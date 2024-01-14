#include "wakeonlan.h"
#include "utils.h"

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <arpa/inet.h>
#include <unistd.h>

wol::AlarmClock::AlarmClock(const char *broadcast, const int &port, const char *targetMac) : mTargetMac(targetMac), mTargetAddress()
{
    mTargetAddress.sin_family = AF_INET;
    mTargetAddress.sin_port = htons(port);
    mTargetAddress.sin_addr.s_addr = inet_addr(broadcast);
}

void wol::AlarmClock::sendWakeUpCall()
{
    // create magic packet buffer
    const int MAC_REPEAT = 16;
    char magicPacket[102];

    // initialize with 6 bytes of 0xFF
    memset(magicPacket, 0xFF, 6);

    // repeat target mac address 16 times
    for (int i = 6; i < 6 + MAC_REPEAT * 6; i += 6)
    {
        sscanf(mTargetMac, "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx",
               &magicPacket[i], &magicPacket[i + 1], &magicPacket[i + 2],
               &magicPacket[i + 3], &magicPacket[i + 4], &magicPacket[i + 5]);
    }

    int udpSocket = createUdpSocket();

    // enable broadcast
    int broadcastEnable = 1;
    setsockopt(udpSocket, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));

    // send packet
    sendto(udpSocket, magicPacket, sizeof(magicPacket), 0, (struct sockaddr *)&mTargetAddress, sizeof(mTargetAddress));

    // close socket
    close(udpSocket);
}

int wol::AlarmClock::createUdpSocket()
{
    int udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udpSocket == -1)
    {
        utils::throwRuntimeException("Error creating socket");
    }
    return udpSocket;
}
