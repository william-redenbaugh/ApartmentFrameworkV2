#include "ClockControl.hpp"

/**************************************************************************/
/*!
    @brief Serial message unpacker the message management class. Will then connect data to other message unpacking functions. 
*/
/**************************************************************************/
void ClockControl::begin(const char *addr, uint16_t port){
    // Setting up network information
    this->clock_addr.sin_family = AF_INET; 
    this->clock_addr.sin_port = htons(port);
    this->clock_addr.sin_addr.s_addr = inet_addr(addr);
}

/**************************************************************************/
/*!
    @brief Sends a sleep command to our clock
*/
/**************************************************************************/
void ClockControl::sleep(void){
    uint8_t off_cmd[5] = {40, 40, 50, 65, 0};    
    // Sending over blank information via udp
    udp_server_sendto(5, off_cmd, &this->clock_addr);
}

/**************************************************************************/
/*!
    @brief Sends a wake command to our clock. 
*/
/**************************************************************************/
void ClockControl::wake(void){
    uint8_t on_cmd[5] = {40, 40, 50, 65, 1};
    // Sending over blank information via udp
    udp_server_sendto(5, on_cmd, &this->clock_addr);
}