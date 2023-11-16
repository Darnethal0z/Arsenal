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

#include <stdio.h>
#include <string.h>
#include <sys/random.h>
// #include <unistd.h> See below (*)
// #include <fcntl.h>

#include "arsenal.h"

// (*) This function is already handled by the linux getrandom() (sys/random.h)
// char generate_random_number(unsigned int * buffer){
//     unsigned int generated_random = 0;
//     int random_dev = open("/dev/urandom", O_RDONLY);

//     if (!random_dev) 
//         return ERROR_OPEN_FILE;

//     if (!read(random_dev, &generated_random, 1)){
//         close(random_dev);
//         return ERROR_READ_FROM_FILE;
//     }

//     close(random_dev);

//     *buffer = generated_random;

//     return 0;
// }

char generate_random_string(const char * charset, char * buffer, int len){
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
