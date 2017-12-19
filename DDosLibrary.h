//
// Created by mao on 17-11-14.
//

#ifndef DDOS_DDOSLIBRARY_H
#define DDOS_DDOSLIBRARY_H

#include <string>
#include <thread>
#include <vector>
#include "arg_bundle.h"

class DDosLibrary {

public:
    explicit DDosLibrary(const arg_bundle &args);

    virtual void run() = 0;

    ~DDosLibrary() = default;

protected:
    void init_socket(int &sock_fd, struct sockaddr_in &server, const char *ip, const int port);

    const arg_bundle args;

    std::vector<std::thread> threads;
};

#endif //DDOS_DDOSLIBRARY_H
