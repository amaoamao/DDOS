//
// Created by mao on 17-11-14.
//

#ifndef DDOS_SLOWLORIS_H
#define DDOS_SLOWLORIS_H

#include "DDosLibrary.h"

class Slowloris : public DDosLibrary {

public:
    explicit Slowloris(const arg_bundle &args);


    void run() override;


private:
    void loris();
};

#endif //DDOS_SLOWLORIS_H
