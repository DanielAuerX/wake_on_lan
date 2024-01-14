#include "utils.h"

#include <iostream>
#include <stdexcept>


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
}
