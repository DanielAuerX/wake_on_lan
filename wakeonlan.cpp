#include "wakeonlan.h"

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

void wol::AlarmClock::sendWakeUpCall(const char *targetMac)
{
    // create magic packet buffer
    const int MAC_REPEAT = 16;
    char magicPacket[102];

    // initialize with 6 bytes of 0xFF
    memset(magicPacket, 0xFF, 6);

    // repeat target mac address 16 times
    for (int i = 6; i < 6 + MAC_REPEAT * 6; i += 6)
    {
        sscanf(targetMac, "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx",
               &magicPacket[i], &magicPacket[i + 1], &magicPacket[i + 2],
               &magicPacket[i + 3], &magicPacket[i + 4], &magicPacket[i + 5]);
    }

    int udpSocket = createUdpSocket();

    // enable broadcast
    int broadcastEnable = 1;
    setsockopt(udpSocket, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));

    // set up the destination address
    sockaddr_in destAddr;
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(9);                            // wol uses port 9
    destAddr.sin_addr.s_addr = inet_addr("255.255.255.255"); // broadcast address

    // send packet
    sendto(udpSocket, magicPacket, sizeof(magicPacket), 0, (struct sockaddr *)&destAddr, sizeof(destAddr));

    // close socket
    close(udpSocket);
}

int wol::AlarmClock::createUdpSocket()
{
    int udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udpSocket == -1)
    {
        std::cerr << "Error creating socket\n";
        return;
    }
    return udpSocket;
}
