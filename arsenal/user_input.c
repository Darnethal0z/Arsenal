/*
 * The Arsenal library
 * Copyright 2023 Darnetha0z
 *
 * This is free software: you are free to change and redistribute it. 
 * There is NO WARRANTY, to the extent permitted by law.
 *
 * This file contains user input features.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "arsenal.h"

void sinput_str(const char * prompt, char * buffer, int len){
    char active_char = 0;
    char* carriage_position = NULL;

    printf("%s", prompt);

    if (fgets(buffer, len, stdin) == NULL) {
        while (active_char != '\n' && active_char != EOF)
            active_char = getchar();
    }

    carriage_position = strchr(buffer, '\n');

    if (carriage_position != NULL){
        *carriage_position = '\0';
    } else{
        while (active_char != '\n' && active_char != EOF)
            active_char = getchar();
    }   
}

int sinput_int(const char * prompt, int * buffer, int len){
    char * end_pointer;
    char read_buffer[len];
    int converted_read_buffer = 0;
  
    sinput_str(prompt, read_buffer, len);
    converted_read_buffer = (int) strtod(read_buffer, &end_pointer);

    if (converted_read_buffer == 0 && strcmp(read_buffer, end_pointer) == 0){
        errno = EIO; // I/O error
        return -1;
    }

    *buffer = converted_read_buffer;

    return 0;
}

int sinput_float(const char * prompt, float * buffer, int len){
    char * end_pointer;
    char read_buffer[len];
    float converted_read_buffer = 0;
    
    sinput_str(prompt, read_buffer, len);
    converted_read_buffer = strtof(read_buffer, &end_pointer);

    if (converted_read_buffer == 0 && strcmp(read_buffer, end_pointer) == 0){
        errno = EIO; // I/O error
        return -1;
    }

    *buffer = converted_read_buffer;

    return 0;
}
