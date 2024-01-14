#include "wakeonlan.h"
#include "utils.h"

int main(int argc, char *const argv[])
{
    std::string broadcast = "255.255.255.255"; // default
    int port = 9;                              // default
    std::string destination;

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
            destination = arg;
        }
    }

    if (destination.empty())
    {
        utils::logError("Error: Missing required <destination> argument!");
        return 1;
    }

    utils::log("Broadcast address: " + broadcast);
    utils::log("Port: " + std::to_string(port));
    utils::log("Mac address: " + destination);

    //call wake up call

    return 0;
}