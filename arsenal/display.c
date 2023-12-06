/*
 * The Arsenal library
 * Copyright 2023 Darnetha0z
 *
 * This is free software: you are free to change and redistribute it. 
 * There is NO WARRANTY, to the extent permitted by law.
 *
 * This file contains a customized version of printf(), permitting
 * stylization of displayed content.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/ioctl.h>

#include "arsenal.h"

// "internal" function
// Counts the digits in an integer
unsigned int _count_int_digits(int value){
    unsigned int count = 0;

    while (value != 0){
        count++;
        value /= 10;
    }
 
    return count;
}

// "internal" function
// Only %i, %s and %s are supported in format
int _get_formatted_str_length(char * format, ...){
    va_list args_list;
    int final_format_length = 0;
    char * str_float;

    va_start(args_list, format);
  
    for (int i = 0; i < (int) strlen(format); i++){
        if (format[i] != '%'){
            final_format_length++;
            continue;
        }

        switch (format[i+1]){
            case ('i'): 
                final_format_length += _count_int_digits(va_arg(args_list, int));
                break;

            case ('s'): 
                final_format_length += strlen(va_arg(args_list, char*));
                break;

            case ('f'):
                // 50 is the size of the float number +1 for the null byte
                str_float = malloc(51 * sizeof(char));

                if (str_float == NULL)
                    return -2;

                // va_arg automatically convert float to double
                sprintf(str_float, "%lf", va_arg(args_list, double));
		        str_float[strlen(str_float)] = '\0';

                final_format_length += strlen(str_float);

                free(str_float);
                break;

            case ('%'): 
                break; // '%' character itself

            default: 
                return -1; // Unsupported format
        }

        i += 2;
    }

    return final_format_length;
}

int stylized_printf(
    const int alignment, 
    const char * color, 
    const char * effect, 
    bool end_by_new_line, 
    char * format, 
    ...){

    va_list args_list;
    va_list args_list_copy;
    struct winsize terminal_window_size;
    
    unsigned int space_padding = 0;
    int formatted_str_length = 0;
    
    char * formatted_str;

    va_start(args_list, format);
    va_copy(args_list_copy, args_list);

    formatted_str_length = _get_formatted_str_length(format, args_list_copy);

    if (formatted_str_length < 0){
        if (formatted_str_length == -1)
            errno = EINVAL; // Invalid argument
        
        return -1;

    }
    
    formatted_str = malloc((formatted_str_length + 1) * sizeof(char));

    if (!formatted_str)
        return -1;

    sprintf(formatted_str, format, args_list);
    formatted_str[formatted_str_length] = '\0';

    switch (alignment) {
        case (ALIGN_LEFT):
            break; // No space padding needed

        case (ALIGN_CENTER):
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal_window_size);
            space_padding = ((terminal_window_size.ws_col / 2) - strlen(formatted_str) / 2);

            break;

        case (ALIGN_RIGHT):
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal_window_size);
            space_padding = terminal_window_size.ws_col - strlen(formatted_str);

            break;

        default:
            errno = EINVAL; // Invalid argument
            return -1;
    }

    if (space_padding != 0) {
        // Iteratively print the spacing
        for (int i = 0; i < space_padding; i++)
            printf(" ");
    }

    printf(
        "%s%s%s\x1b[0m",
        color,
        effect,
        formatted_str);

    if (end_by_new_line)
        printf("\n");

    free(formatted_str);
    va_end(args_list);

    return 0;
}
