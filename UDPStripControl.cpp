#include "UDPStripControl.h"
#include <iostream>

/*
Function: const char *addr, uint16_t port, uint16_t num_leds
Description: sets up communicatation with a strip controlled via udp
Parameters: const char *addr(string ip address of strip), uint16_t port(port of strip), uint16_t num_leds(number of LEDs in strip)
Return: none
*/
void UDPStripControl::begin(const char *addr, uint16_t port, uint16_t num_leds){
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

/*
Function: end(void)
Description: dereferences allocated array for controlling strip via UDP
Parameters: none
Return: none 
*/
void UDPStripControl::end(void){
    delete[] this->data_arr;
}

/*
Function: update(void)
Description: sends UDP array buffer to LED strip
Parameters: none
Return: none
*/
void UDPStripControl::update(void){
    // Sending over information via udp
    udp_server_sendto(this->arr_size, this->data_arr, &this->led_strip_addr);
}

/*
Function: set_led(uint8_t r, uint8_t g, uint8_t b, uint16_t led)
Description: allows us to modify array buffer to show LED strip changes
Parameters: uint8_t r, uint8_t g, uint8_t b,(rgb color value of pixel) uint16_t led(position down the strip)
Return: 
*/
void UDPStripControl::set_led(uint8_t r, uint8_t g, uint8_t b, uint16_t led){
    // Don't wanna go out of bounds :0 and cause a segfault :(
    if(led < this->num_leds){
        this->data_arr[led * 3] = r;
        this->data_arr[led * 3 + 1] = g;
        this->data_arr[led * 3 + 2] = b;
    }
}

/*
Function: set_strip(uint8_t r, uint8_t g, uint8_t b)
Description: allows us to modify whole strip array buffer to a specific color 
Parameters: uint8_t r, uint8_t g, uint8_t b(rgb color value. )
Return: none
*/
void UDPStripControl::set_strip(uint8_t r, uint8_t g, uint8_t b){
    for(uint16_t i = 0; i < this->num_leds; i++){
        this->set_led(r, g, b, i);
    }
}

