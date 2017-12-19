//
// Created by mao on 17-12-19.
//

#ifndef DDOS_UTILS_H
#define DDOS_UTILS_H

#include <vector>
#include <string>

namespace utils {
    std::vector<std::string> split(const std::string &s, const std::string &seperator);

    void exec(std::string cmd);

    char *getCmdOption(char **begin, char **end, const std::string &option);

    bool cmdOptionExists(char **begin, char **end, const std::string &option);

    std::string join(const std::vector<std::string> &v, unsigned long start, unsigned long end);
}
#endif //DDOS_UTILS_H
