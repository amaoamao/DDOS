//
// Created by mao on 17-11-15.
//

#ifndef DDOS_ARG_BUNDLE_H
#define DDOS_ARG_BUNDLE_H


class arg_bundle {
public:
    const char target_ip[20];
    uint16_t target_port;
    int thread_num;
};


#endif //DDOS_ARG_BUNDLE_H
