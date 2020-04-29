#include "UDPStripControl.h"
#include <iostream>

void UDPStripControl::begin(const char *addr, uint16_t port, uint16_t num_leds){
    udp_server_socket_open(4400);
    this->led_strip_addr.sin_family = AF_INET; 
    this->led_strip_addr.sin_port = htons(port);
    this->led_strip_addr.sin_addr.s_addr = inet_addr(addr);

    // Defining an array on the heap and keeping it's size saved :0
    this->data_arr = new uint8_t[(num_leds * 3 + 100)];
    this->num_leds = num_leds;
    this->arr_size = num_leds * 3 + 100; 

    for(uint16_t i = 0; i < num_leds * 3 + 100; i++){
        this->data_arr[i] = 0;
    }

    this->update();
}

void UDPStripControl::update(void){
    // Sending over information via udp
    udp_server_sendto(this->arr_size, this->data_arr, &this->led_strip_addr);
}

void UDPStripControl::set_led(uint8_t r, uint8_t g, uint8_t b, uint16_t led){
    // Don't wanna go out of bounds :0 and cause a segfault :(
    if(led < this->num_leds){
        this->data_arr[led * 3] = r;
        this->data_arr[led * 3 + 1] = g;
        this->data_arr[led * 3 + 2] = b;
    }
}