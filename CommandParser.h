//
// Created by mao on 17-12-19.
//

#ifndef DDOS_COMMANDPARSER_H
#define DDOS_COMMANDPARSER_H


#include "DDosLibrary.h"

class CommandParser {
public:
    DDosLibrary *parse(const std::string &command);

    bool hasError();

    std::string getMessage();

private:
    const std::string commandSYN = "syn";
    const std::string commandLoris = "loris";
    const std::string commandLoad = "load";
    const std::string commandSSH = "ssh";
    bool error = false;
    std::string message;
};


#endif //DDOS_COMMANDPARSER_H
