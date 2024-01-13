#include <iostream>


int main()
{
    const char *targetMac = "00:11:22:33:44:55";
    std::cout << "Sending magic packet to " << targetMac << "\n";
    return 0;
}