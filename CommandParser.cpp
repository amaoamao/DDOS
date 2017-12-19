//
// Created by mao on 17-12-19.
//

#include <iostream>
#include <cstring>
#include <numeric>
#include "CommandParser.h"
#include "Slowloris.h"
#include "Utils.h"
#include "ConfigLibrary.h"
#include "SSH.h"

DDosLibrary *CommandParser::parse(const std::string &command) {
    error = false;
    message = "";
    std::vector<std::string> tokens = utils::split(command, " ");
    DDosLibrary *library = nullptr;
    arg_bundle args{};
    if (tokens.empty()) {
        error = true;
        return nullptr;
    }
    if (tokens[0] == commandSSH) {
        if (tokens.size() != 5) {
            error = true;
            message = "Wrong argument format.\nUsage: ssh [command] [targetHost] [targetPort] [threadCount]";
        } else {
            strcpy(const_cast<char *>(args.target_ip), tokens[2].c_str());
            args.target_port = static_cast<uint16_t>(std::atoi(tokens[3].c_str()));
            args.thread_num = std::atoi(tokens[4].c_str());
            library = new SSH(args, tokens[1]);
        }
    } else if (tokens[0] == commandSYN) {
        error = true;
        message = "Unimplemented.";
    } else if (tokens[0] == commandLoris) {
        if (tokens.size() != 4) {
            error = true;
            message = "Wrong argument format.\nUsage: loris [targetHost] [targetPort] [threadCount]";
        } else {
            strcpy(const_cast<char *>(args.target_ip), tokens[1].c_str());
            args.target_port = static_cast<uint16_t>(std::atoi(tokens[2].c_str()));
            args.thread_num = std::atoi(tokens[3].c_str());
            library = new Slowloris(args);
        }
    } else if (tokens[0] == commandLoad) {
        if (tokens.size() != 2) {
            error = true;
            message = "Wrong argument format.\nUsage: load [filename]";
        } else {
            error = true;
            ConfigLibrary configLibrary;
            configLibrary.load(tokens[1]);
        }
    } else {
        error = true;
        message = "Wrong command [" + tokens[0] + "]\nCommand could be\n\tsyn\n\tloris\n\tload\n\tssh";
    }
    return library;
}

bool CommandParser::hasError() {
    return error;
}

std::string CommandParser::getMessage() {
    return message;
}
