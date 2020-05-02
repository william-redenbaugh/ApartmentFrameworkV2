#include "ClockControl.hpp"

/*
Function: begin(const char *addr, uint16_t port)
Description: allows us to set up commands to Tina's clock via UDP
Parameters: const char *addr(ip address of device), uint16_t port(port of device)
Return: none
*/
void ClockControl::begin(const char *addr, uint16_t port){
    // Setting up network information
    this->clock_addr.sin_family = AF_INET; 
    this->clock_addr.sin_port = htons(port);
    this->clock_addr.sin_addr.s_addr = inet_addr(addr);
}

/*
Function: sleep(void)
Description: sends UDP sleep command 
Parameters: none
Return: none
*/
void ClockControl::sleep(void){
    uint8_t off_cmd[5] = {40, 40, 50, 65, 0};    
    // Sending over blank information via udp
    udp_server_sendto(5, off_cmd, &this->clock_addr);
}

/*
Function: wake(void)
Description: sends UDP wake command
Parameters: none
Return: none
*/
void ClockControl::wake(void){
    uint8_t on_cmd[5] = {40, 40, 50, 65, 1};
    // Sending over blank information via udp
    udp_server_sendto(5, on_cmd, &this->clock_addr);
}