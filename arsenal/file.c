/*
 * The Arsenal library
 * Copyright 2023 Darnetha0z
 *
 * This is free software: you are free to change and redistribute it. 
 * There is NO WARRANTY, to the extent permitted by law.
 *
 * This file contains file manipulation features.
 *
 */

#include "arsenal.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// Get a file size.
int get_file_size(char * file_path){
	struct stat file_info;

	if (stat(file_path, &file_info) != 0)
		return -1;

	return file_info.st_size;
}

// Read a file recursively, and completely.
int read_file(char * file_path, char * buffer, size_t buffsize){
	int fd, retval = 0;

	if (!(fd = open(file_path, O_RDONLY)))
		return -1;

	while ((retval = read(fd, buffer, buffsize))){}

	close(fd);

	return retval == -1 ? -1 : 0;
}