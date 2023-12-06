/*
 * The Arsenal library
 * Copyright 2023 Darnetha0z
 *
 * This is free software: you are free to change and redistribute it. 
 * There is NO WARRANTY, to the extent permitted by law.
 *
 * This is the header of the Arsenal library.
 *
 */

#ifndef _ARSENAL_ONCE
#define _ARSENAL_ONCE

#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ALIGN_LEFT                        1
#define ALIGN_CENTER                      2
#define ALIGN_RIGHT                       3

#define COLOR_NONE                        ""
#define COLOR_RED                         "\x1b[31m"
#define COLOR_GREEN                       "\x1b[32m"
#define COLOR_YELLOW                      "\x1b[33m"
#define COLOR_BLUE                        "\x1b[34m"
#define COLOR_MAGENTA                     "\x1b[35m"
#define COLOR_CYAN                        "\x1b[36m"

#define EFFECT_NONE                       ""
#define EFFECT_BOLD                       "\x1b[1m"
#define EFFECT_ITALIC                     "\x1b[3m"
#define EFFECT_FAINT                      "\x1b[2m"
#define EFFECT_UNDERLINE                  "\x1b[4m"
#define EFFECT_SLOW_BLINK                 "\x1b[5m"
#define EFFECT_FAST_BLINK                 "\x1b[6m"
#define EFFECT_SWAP_COLORS                "\x1b[7m"

// URL-safe characters
#define RANDOM_STRING_DEFAULT_CHARSET     "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-."

typedef struct {

    int socket;
    struct sockaddr_in in;

} SERVER_CONTEXT;

typedef struct {

    int socket;
    struct sockaddr_in in;

} CLIENT_CONTEXT;

// print.c

// "Internal" functions used by others features below
// unsigned int _count_int_digits(int value);
// int _get_formatted_str_length(char * format, ...);

extern int stylized_printf(
    const int alignment, 
    const char * color, 
    const char * effect, 
    bool end_by_new_line, 
    char * format, 
    ...);

// string.c
extern void concatenate_strings(int n, char * buffer, ...);
extern void split_string(char * string, char * buffer, char separator, int ocurence_index);

// user_input.c
extern void sinput_str(const char * prompt, char * buffer, int len);
extern int sinput_int(const char * prompt, int * buffer, int len);
extern int sinput_float(const char * prompt, float * buffer, int len);

// network.c
extern int close_socket(int socket_fd);
extern int initialize_server_instance(SERVER_CONTEXT * server_context, int listen_port);
extern int accept_client(SERVER_CONTEXT server_context, CLIENT_CONTEXT * client_context, int backlog);
extern int connect_server(CLIENT_CONTEXT * client_context, char * server_ip, int server_port);
extern int ssend_str(int socket_fd, char * buffer, int len);
extern int srecv_str(int socket_fd, char * buffer, int len);
extern int ssend_int(int socket_fd, int buffer);
extern int srecv_int(int socket_fd, int * buffer);

// random.c
extern int generate_random_string(const char * charset, char * buffer, int len);

#endif // _ARSENAL_ONCE
