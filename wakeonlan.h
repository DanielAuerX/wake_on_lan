#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

namespace wol
{
    class AlarmClock
    {
    public:
        AlarmClock(const char *broadcast, const int &port, const char *targetMac);
        void sendWakeUpCall();

    private:
        struct sockaddr_in mTargetAddress;
        const char *mTargetMac;
        int createUdpSocket();
    };
}