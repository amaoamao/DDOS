//
// Created by mao on 17-12-19.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "ConfigLibrary.h"

std::vector<ConfigLibrary::Host> ConfigLibrary::hosts;

void ConfigLibrary::load(std::string fileName) {
    std::ifstream infile(fileName);
    std::string line;
    hosts.clear();
    while (std::getline(infile, line)) {
        Host host(line);
        hosts.push_back(std::move(host));
    }
    std::cout << hosts.size() << " hosts loaded successfully" << std::endl;
}

void ConfigLibrary::dump(std::string fileName) {
    std::ofstream outfile(fileName);
    for (const Host &host : hosts) {
        outfile << host.url << std::endl;
    }
    outfile.close();
    std::cout << hosts.size() << " hosts dumped successfully" << std::endl;
}
