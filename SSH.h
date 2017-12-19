//
// Created by mao on 17-12-20.
//

#ifndef DDOS_SSH_H
#define DDOS_SSH_H


#include "DDosLibrary.h"
#include "ConfigLibrary.h"

class SSH : public DDosLibrary {
public:
    explicit SSH(arg_bundle args, const std::string &string);


    void run() override;

private:
    void connect(const ConfigLibrary::Host &host);

    const std::string command;
};


#endif //DDOS_SSH_H
