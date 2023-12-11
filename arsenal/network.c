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

// Nessessary headers are included inside.
#include "arsenal.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

// Socket management functions

int close_socket(int socket_fd){
    if (shutdown(socket_fd, 2) == -1)
        return -1;

    if (close(socket_fd) == -1)
        return -1;

    return 0;
}

int initialize_server_instance(SERVER_CONTEXT * server_context, int listen_port){
    int opt = 1;

    server_context->socket = socket(AF_INET, SOCK_STREAM, 0);

    if (!server_context->socket)
        return -1;

    if (setsockopt(
        server_context->socket, 
        SOL_SOCKET, 
        SO_REUSEADDR, 
        &opt, sizeof(opt)) == -1){

        close_socket(server_context->socket);
        return -1;
    }

    server_context->in.sin_addr.s_addr = INADDR_ANY;
    server_context->in.sin_family = AF_INET;
    server_context->in.sin_port = htons(listen_port);

    if (bind(
        server_context->socket, 
        (struct sockaddr *) &server_context->in, 
        sizeof(server_context->in)) == -1){

        close_socket(server_context->socket);
        return -1;
    }

    return 0;
}

int accept_client(SERVER_CONTEXT server_context, CLIENT_CONTEXT * client_context, int backlog){
    int in_len = sizeof(client_context->in);

    /*
     * listen() is a blocking instruction, this is why it is called
     * in the function that accepts clients.
     */
    if (listen(server_context.socket, backlog) == -1){
        close_socket(server_context.socket);
        return -1;
    }

    client_context->socket = accept(
        server_context.socket, 
        (struct sockaddr *) &client_context->in, 
        (socklen_t*) &in_len);

    if (client_context->socket == -1)
        return -1;

    return 0;
}

int connect_server(CLIENT_CONTEXT * client_context, char * server_ip, int server_port){
    client_context->socket = socket(AF_INET, SOCK_STREAM, 0);

    if (!client_context->socket)
        return -1;

    client_context->in.sin_family = AF_INET;
    client_context->in.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_ip, &client_context->in.sin_addr) <= 0){
        close_socket(client_context->socket);
        return -1;
    } 

    if (connect(
        client_context->socket, 
        (struct sockaddr *) &client_context->in, 
        sizeof(client_context->in)) != 0){

        close_socket(client_context->socket);
        return -1;
    }

    return 0;
}

// Data transmission functions

int ssend_str(int socket_fd, char * buffer, int len){
    if (send(socket_fd, buffer, len * sizeof(char), 0) == -1)
        return -1;

    return 0;
}

int srecv_str(int socket_fd, char * buffer, int len){
    if (recv(socket_fd, buffer, (len * sizeof(char)), 0) == -1)
        return -1;

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
