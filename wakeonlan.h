#pragma once

namespace wol{
    class AlarmClock{
        public:
            void sendWakeUpCall(const char* targetMac);

        private:
        int createUdpSocket(); 

    };
}