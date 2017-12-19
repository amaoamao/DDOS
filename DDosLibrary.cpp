//
// Created by mao on 17-11-14.
//
#include <sys/socket.h>
#include <cstdio>
#include <arpa/inet.h>
#include "DDosLibrary.h"


void DDosLibrary::init_socket(int &sock_fd, struct sockaddr_in &server, const char *ip, const int port) {
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Creating socket");
        return;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(static_cast<uint16_t>(port));
}

DDosLibrary::DDosLibrary(const arg_bundle &args) : args(args) {
}
