/*
 * The Arsenal library
 * Copyright 2023 Darnetha0z
 *
 * This is free software: you are free to change and redistribute it. 
 * There is NO WARRANTY, to the extent permitted by law.
 *
 * This is a file containing a dummy main() function, used for testing purposes only.
 *
 */

#include <stdio.h>
#include <string.h>

#include "arsenal.h"

int count_character_occurences(char * string, char character){
    int result = 0;
    
    for (int i = 0; string[i] != '\0'; i++){
        if(string[i] == character)
            result++;
    }

    return ++result;
}

// Test purposes only
int main(int argc, char * argv[]){
    char string[] = "Here we are in the Arsenal documentation";
    char buffer[14];

    printf("%i\n", count_character_occurences(string, ' '));

    for ( int i = 0; i < 7; i++ ){
        split_string(string, buffer, ' ', i);
        printf("Occurence no %i : %s\n", i + 1, buffer);
    }

    return 0;
}
