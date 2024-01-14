#pragma once

#include <string>

namespace utils{

void log(const std::string &message);
void logError(const std::string &message);
void throwRuntimeException(const std::string &message);
bool isValidBroadcastAddress(const std::string& broadcast);
bool isValidMacAddress(const std::string& mac);

}