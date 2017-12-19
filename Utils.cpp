//
// Created by mao on 17-12-19.
//

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include "Utils.h"

std::vector<std::string> utils::split(const std::string &s, const std::string &seperator) {
    std::vector<std::string> result;
    typedef std::string::size_type string_size;
    string_size i = 0;
    if (s.empty())
        return result;
    while (i != s.size()) {
        int flag = 0;
        while (i != s.size() && flag == 0) {
            flag = 1;
            for (char x : seperator)
                if (s[i] == x) {
                    ++i;
                    flag = 0;
                    break;
                }
        }
        flag = 0;
        string_size j = i;
        while (j != s.size() && flag == 0) {
            for (char x : seperator)
                if (s[j] == x) {
                    flag = 1;
                    break;

                }
            if (flag == 0)
                ++j;
        }
        if (i != j) {
            result.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return result;
}

void utils::exec(std::string cmd) {
    char buffer[128];
    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != nullptr)
                std::cout << buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
}


char *utils::getCmdOption(char **begin, char **end, const std::string &option) {
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return nullptr;
}

bool utils::cmdOptionExists(char **begin, char **end, const std::string &option) {
    return std::find(begin, end, option) != end;
}

std::string utils::join(const std::vector<std::string> &v, unsigned long start, unsigned long end) {
    std::string temp;
    for (unsigned long i = start; i < v.size(); ++i) {
        temp += v.at(i);
    }
    return temp;
}