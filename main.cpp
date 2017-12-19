#include <iostream>
#include <csignal>
#include <zconf.h>
#include "DDosLibrary.h"
#include "CommandParser.h"
#include "Utils.h"

std::vector<DDosLibrary *> jobs;


void quit() {
    for (DDosLibrary *job : jobs) {
        delete (job);
    }
    exit(0);
}

void INTHandler(int sig) {
    char c;

    signal(sig, SIG_IGN);
    if (!jobs.empty()) {
        std::cout << ("You have running jobs background, do you really want to quit? [y/n] ");
        c = static_cast<char>(getchar());
        if (c == 'y' || c == 'Y') {
            quit();
        } else {
            signal(SIGINT, INTHandler);
        }
    } else {
        quit();
    }
}

int main(int argc, char *argv[]) {
    CommandParser parser;
    if (utils::cmdOptionExists(argv, argv + argc, "-sh")) {
        char hostname[HOST_NAME_MAX];
        gethostname(hostname, HOST_NAME_MAX);
        std::string command(utils::getCmdOption(argv, argv + argc, "-sh"));
        std::cout << hostname << " Connected. Executing: \"" + command << "\"" << std::endl;
        DDosLibrary *library = parser.parse(command);
        if (parser.hasError()) {
            if (!parser.getMessage().empty())
                std::cout << parser.getMessage() << std::endl;
        } else {
            jobs.push_back(library);
            library->run();
        }
    } else {
        std::string command;
        signal(SIGINT, INTHandler);
        while (!std::cin.eof()) {
            std::cout << ">>>";
            std::getline(std::cin, command);
            if (command.empty())
                continue;
            DDosLibrary *library = parser.parse(command);
            if (parser.hasError()) {
                if (!parser.getMessage().empty())
                    std::cout << parser.getMessage() << std::endl;
                continue;
            } else {
                jobs.push_back(library);
                library->run();
            }
        }
    }
    quit();
    return 0;
}