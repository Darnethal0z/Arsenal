/*
 * The Arsenal library
 * Copyright 2023 Darnetha0z
 *
 * This is free software: you are free to change and redistribute it. 
 * There is NO WARRANTY, to the extent permitted by law.
 *
 * This is a file containing a dummy main() function, used for testing purposes only.
 * This file is omitted if Arsenal is build with the installation script.
 *
 */

#include "arsenal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Test purposes only
int main(int argc, char * argv[]){
    int size = get_file_size("/etc/passwd");

    printf("%i\n", size);

    char * buffer = malloc(size * sizeof(char));

    read_file("/etc/passwd", buffer);

    printf("%s\n", buffer);

    return 0;
}
