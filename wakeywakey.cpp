#include "wakeonlan.h"
#include "utils.h"

#include <string>

int main(int argc, char *const argv[])
{
    std::string broadcast = "255.255.255.255"; // default
    int port = 9;                              // default
    std::string target;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-b" && i + 1 < argc)
        {
            broadcast = argv[++i];
        }
        else if (arg == "-p" && i + 1 < argc)
        {
            port = std::stoi(argv[++i]);
        }
        else
        {
            target = arg;
        }
    }

    if (target.empty())
    {
        utils::logError("Error: Missing required <target> argument! The argument must contain the target's Mac address.\nUsage: wake_on_lan [-b <broadcast>] [-p <port>] <target>");
        return 1;
    }

    if (!utils::isValidBroadcastAddress(broadcast))
    {
        utils::logError("Error: Invalid broadcast address!");
        return 1;
    }

    if (!utils::isValidMacAddress(target))
    {
        utils::logError("Error: Invalid Mac address!");
        return 1;
    }

    utils::log("Broadcast address: " + broadcast);
    utils::log("Port: " + std::to_string(port));
    utils::log("Mac address: " + target);

    wol::AlarmClock alarmClock = wol::AlarmClock(broadcast.c_str(), port, target.c_str());

    alarmClock.sendWakeUpCall();

    return 0;
}