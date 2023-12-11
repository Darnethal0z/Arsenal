/*
 * The Arsenal library
 * Copyright 2023 Darnetha0z
 *
 * This is free software: you are free to change and redistribute it. 
 * There is NO WARRANTY, to the extent permitted by law.
 *
 * This file contains random number / string generation features.
 *
 */

#include "arsenal.h"

#include <stdio.h>
#include <string.h>
#include <sys/random.h>

int generate_random_string(const char * charset, char * buffer, int len){
    unsigned int generated_random = 0;
    int charset_length = strlen(charset) - 1;

    for (int i = 0; i < len - 1; i++){
        if (getrandom(&generated_random, 1, GRND_RANDOM) == -1)
            return -1;

        buffer[i] = charset[generated_random % charset_length];
    }

    buffer[len - 1] = '\0';

    return 0;
}
