/*
 * The Arsenal library
 * Copyright 2023 Darnetha0z
 *
 * This is free software: you are free to change and redistribute it. 
 * There is NO WARRANTY, to the extent permitted by law.
 *
 * This file contains client / server socket manipulation features.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "arsenal.h"

// Socket management functions

int close_socket(int socket_fd){
    if (shutdown(socket_fd, 2) == -1)
        return -1;

    if (close(socket_fd) == -1)
        return -1;

    return 0;
}

int initialize_server_instance(SERVER_CONTEXT * server_context){
    int opt = 1;

    server_context->s_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (!server_context->s_sock)
        return -1;

    if (setsockopt(
        server_context->s_sock, 
        SOL_SOCKET, 
        SO_REUSEADDR, 
        &opt, sizeof(opt)) == -1){
        
        close_socket(server_context->s_sock);
        return -1;
    }

    server_context->s_in.sin_addr.s_addr = INADDR_ANY;
    server_context->s_in.sin_family = AF_INET;
    server_context->s_in.sin_port = htons(server_context->s_lport);

    if (bind(
        server_context->s_sock, 
        (struct sockaddr *) &server_context->s_in, 
        sizeof(server_context->s_in)) == -1){
        
        close_socket(server_context->s_sock);
        return -1;
    }

    if (listen(server_context->s_sock, server_context->s_backlog) == -1){
        close_socket(server_context->s_sock);
        return -1;
    }

    return 0;
}

int accept_client(SERVER_CONTEXT server_context, CLIENT_CONTEXT * client_context){
    int c_in_len = sizeof(client_context->c_in);

    client_context->c_sock = accept(
        server_context.s_sock, 
        (struct sockaddr *) &client_context->c_in, 
        (socklen_t*) &c_in_len);

    if (client_context->c_sock == -1)
        return -1;

    return 0;
}

int connect_server(CLIENT_CONTEXT * client_context){
    client_context->c_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (!client_context->c_sock)
        return -1;

    client_context->c_in.sin_family = AF_INET;
    client_context->c_in.sin_port = htons(client_context->r_port);

    if (inet_pton(
        AF_INET,
        client_context->r_address,
        &client_context->c_in.sin_addr) <= 0){

        close_socket(client_context->c_sock);
        return -1;
    } 

    if (connect(
        client_context->c_sock, 
        (struct sockaddr *) &client_context->c_in, 
        sizeof(client_context->c_in)) != 0){

        close_socket(client_context->c_sock);
        return -1;
    }

    return 0;
}

// Data transmission functions

int ssend_str(int socket_fd, char * buffer, int len){
    buffer[len - 1] = '\0';

    if (send(socket_fd, buffer, len * sizeof(char), 0) == -1)
        return -1;

    return 0;
}

int srecv_str(int socket_fd, char * buffer, int len){
    if (recv(socket_fd, buffer, (len * sizeof(char)), 0) == -1)
        return -1;

    buffer[len - 1] = '\0';

    return 0;
}

int ssend_int(int socket_fd, int buffer){
    buffer = htonl(buffer);

    if (send(socket_fd, (const char*) &buffer, sizeof(buffer), 0) == -1)
        return -1;

    return 0;
}

int srecv_int(int socket_fd, int * buffer){
    int recv_buffer = 0;

    if (recv(socket_fd, (char *) &recv_buffer, sizeof(recv_buffer), 0) == -1)
        return -1;

    *buffer = (int) ntohl(recv_buffer);

    return 0;
}
