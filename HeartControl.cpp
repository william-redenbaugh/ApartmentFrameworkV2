#include "HeartControl.hpp"

/*
Function: begin(const char *addr, uint16_t port)
Description: sets up the UDP server settings to control Tina's heart via UDP packets. 
Parameters: const char *addr(string array of the ip address), uint16_t port(port number )
Returns: 
*/
void HeartControl::begin(const char *addr, uint16_t port){
    // Setting up network information
    this->heart_addr.sin_family = AF_INET; 
    this->heart_addr.sin_port = htons(port);
    this->heart_addr.sin_addr.s_addr = inet_addr(addr);
}

/*
Function: lock(void) 
Description: Sends udp command to lock the heart
Parameters: none
Returns: none
*/
void HeartControl::lock(void){
    uint8_t lock_cmd[4] = {20, 20, 30, 90};
    udp_server_sendto(4, lock_cmd, &this->heart_addr);
}

/*
Function: unlock(void)
Description: sends the unlock UDP command to the heart
Parameters: none 
Returns: none
*/
void HeartControl::unlock(void){
    uint8_t unlock_cmd[4] = {20, 20, 30, 91};
    udp_server_sendto(4, unlock_cmd, &this->heart_addr);
}

/*
Function: toggle_lamp(void)
Description: Sends the toggle lamp udp command to the heart
Parameters: none
Returns: none 
*/
void HeartControl::toggle_lamp(void){
    uint8_t toggle_lamp_cmd[4] = {50, 50, 30, 92};
    udp_server_sendto(4, toggle_lamp_cmd, &this->heart_addr);
}

/*
Function: lamp_on(void)
Description: sends the lamp on udp command to the heart
Parameters: none
Returns: none
*/
void HeartControl::lamp_on(void){
    uint8_t lamp_on_cmd[4] = {50, 50, 30, 91};
    udp_server_sendto(4, lamp_on_cmd, &this->heart_addr);
}

/*
Function: lamp_off(void)
Description: sends the lamp off udp command to the heart
Parameters: none
Returns: none
*/
void HeartControl::lamp_off(void){
    uint8_t lamp_off_cmd[4] = {50, 50, 30, 90};
    udp_server_sendto(4, lamp_off_cmd, &this->heart_addr);
}

/*
Function: beep(void)
Description: sends the beep udp command to the heart
Parameters: none
Returns: none
*/
void HeartControl::beep(void){
    uint8_t beep_cmd[4] = {12, 12, 12, 12};
    udp_server_sendto(4, beep_cmd, &this->heart_addr);
}