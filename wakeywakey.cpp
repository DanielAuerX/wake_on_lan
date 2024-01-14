#include "wakeonlan.h"
#include "utils.h"

#include <string>

struct WakeOnLanConfig
{
    std::string broadcast = "192.168.1.255"; // default
    int port = 9;                            // default
    std::string target;
};

void setCliArguments(int argc, char *const argv[], WakeOnLanConfig &config)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-b" && i + 1 < argc)
        {
            config.broadcast = argv[++i];
        }
        else if (arg == "-p" && i + 1 < argc)
        {
            config.port = std::stoi(argv[++i]);
        }
        else
        {
            config.target = arg;
        }
    }
}

void validateCliArguments(std::string &target, std::string &broadcast)
{
    if (target.empty())
    {
        utils::throwRuntimeException("Error: Missing required <target> argument! The argument must contain the target's Mac address.\nUsage: wake_on_lan [-b <broadcast>] [-p <port>] <target>");
    }

    if (!utils::isValidBroadcastAddress(broadcast))
    {
        utils::throwRuntimeException("Error: Invalid broadcast address!");
    }

    if (!utils::isValidMacAddress(target))
    {
        utils::throwRuntimeException("Error: Invalid Mac address!");
    }
}

int main(int argc, char *const argv[])
{
    WakeOnLanConfig config;

    setCliArguments(argc, argv, config);

    validateCliArguments(config.target, config.broadcast);

    utils::log("Broadcast address: " + config.broadcast + "\nPort: " + std::to_string(config.port) + "\nMac address: " + config.target + "\nSending magic packet...");

    wol::AlarmClock alarmClock(config.broadcast.c_str(), config.port, config.target.c_str());

    alarmClock.sendWakeUpCall();

    utils::log("Sent magic packet to " + config.target);

    return 0;
}


