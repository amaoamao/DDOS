//
// Created by mao on 17-12-19.
//

#ifndef DDOS_CONFIGLIBRARY_H
#define DDOS_CONFIGLIBRARY_H


#include <utility>

#include "DDosLibrary.h"
#include "CommandParser.h"
#include "Utils.h"

class ConfigLibrary {

public:
    void load(std::string fileName);

    void dump(std::string fileName);

    class Host {
    private:
        std::vector<std::string> args;
    public:
        const std::string url;

        explicit Host(std::string url) : url(std::move(url)) {
            for (const std::string &str :utils::split(this->url, "@")) {
                std::vector<std::string> temp = utils::split(str, ":");
                args.insert(args.end(), temp.begin(), temp.end());
            }
            if (args.size() != 3) {
                std::cout << "Wrong host url format [" << this->url << "]" << std::endl;
                url = "";
            }
        }

        std::string getUserName() const {
            return args[0];
        }

        std::string getPassword() const {
            return args[1];
        }

        std::string getHost() const {
            return args[2];
        }
    };

    static std::vector<ConfigLibrary::Host> hosts;

};


#endif //DDOS_CONFIGLIBRARY_H
