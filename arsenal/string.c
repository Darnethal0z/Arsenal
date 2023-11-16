/*
 * The Arsenal library
 * Copyright 2023 Darnetha0z
 *
 * This is free software: you are free to change and redistribute it. 
 * There is NO WARRANTY, to the extent permitted by law.
 *
 * This file contains string manipulation features.
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "arsenal.h"

void concatenate_strings(int n, char * buffer, ...){
    va_list args_list;

    va_start(args_list, buffer);

    for (int i = 0; i < n; i++)
        strcat(buffer, va_arg(args_list, char*));

    buffer[strlen(buffer)] = '\0';

    va_end(args_list);
}

void split_string(char * string, char * buffer, char separator, int occurence_index){
    int occurence_counter = 0, separator_index = 0, j = 0;

    for (
        separator_index = 0;
        separator_index < (int) strlen(string);
        separator_index++){

        if (string[separator_index] == separator)
            occurence_counter++;

        if (occurence_counter == occurence_index)
            break;
    }

    for (
        int i = separator_index + (string[separator_index] == separator ? 1 : 0); 
        i < (int) strlen(string); 
        i++){

        if (string[i] == separator)
            break;

        buffer[j] = string[i];
        j++;
    }

    buffer[j] = '\0';
}