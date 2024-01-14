#include "utils.h"

#include <iostream>
#include <stdexcept>
#include <regex>

namespace utils
{

    void log(const std::string &message)
    {
        std::cout << message << std::endl;
    }

    void logError(const std::string &message)
    {
        std::cerr << message << std::endl;
    }

    void throwRuntimeException(const std::string &message)
    {
        throw std::runtime_error(message);
    }
    bool isValidBroadcastAddress(const std::string &broadcast)
    {
        const std::regex ipv4Regex("^(25[0-5]|2[0-4][0-9]|[0-1]?[0-9][0-9]?)\\."
                                   "(25[0-5]|2[0-4][0-9]|[0-1]?[0-9][0-9]?)\\."
                                   "(25[0-5]|2[0-4][0-9]|[0-1]?[0-9][0-9]?)\\."
                                   "(25[0-5]|2[0-4][0-9]|[0-1]?[0-9][0-9]?)$");
        return std::regex_match(broadcast, ipv4Regex);
    }
    bool isValidMacAddress(const std::string &mac)
    {
        const std::regex macRegex("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
        return std::regex_match(mac, macRegex);
    }
}
