#include "HeartControl.hpp"

void HeartControl::begin(const char *addr, uint16_t port){
    // Setting up network information
    this->heart_addr.sin_family = AF_INET; 
    this->heart_addr.sin_port = htons(port);
    this->heart_addr.sin_addr.s_addr = inet_addr(addr);
}

void HeartControl::lock(void){
    uint8_t lock_cmd[4] = {20, 20, 30, 90};
    udp_server_sendto(4, lock_cmd, &this->heart_addr);
}

void HeartControl::unlock(void){
    uint8_t unlock_cmd[4] = {20, 20, 30, 91};
    udp_server_sendto(4, unlock_cmd, &this->heart_addr);
}

void HeartControl::toggle_lamp(void){
    uint8_t toggle_lamp_cmd[4] = {50, 50, 30, 92};
    udp_server_sendto(4, toggle_lamp_cmd, &this->heart_addr);
}

void HeartControl::lamp_on(void){
    uint8_t lamp_on_cmd[4] = {50, 50, 30, 91};
    udp_server_sendto(4, lamp_on_cmd, &this->heart_addr);
}

void HeartControl::lamp_off(void){
    uint8_t lamp_off_cmd[4] = {50, 50, 30, 90};
    udp_server_sendto(4, lamp_off_cmd, &this->heart_addr);
}

void HeartControl::beep(void){
    uint8_t beep_cmd[4] = {12, 12, 12, 12};
    udp_server_sendto(4, beep_cmd, &this->heart_addr);
}