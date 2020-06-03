#include "UDPStripControl.h"
#include <iostream>

/**************************************************************************/
/*!
    @brief Starts up our UDP controling. 
    @param const char *addr(the ip address of our device as a string), uint16_t port(port of our device), uint16_t num_leds(number of LEDs our device has. )
*/
/**************************************************************************/
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

/**************************************************************************/
/*!
    @brief Frees up the memory that this object uses. 
*/
/**************************************************************************/
void UDPStripControl::end(void){
    delete[] this->data_arr;
}

/**************************************************************************/
/*!
    @brief sends out our data via udp. 
*/
/**************************************************************************/
void UDPStripControl::update(void){
    // Sending over information via udp
    udp_server_sendto(this->arr_size, this->data_arr, &this->led_strip_addr);
}

/**************************************************************************/
/*!
    @brief sets the LED to a particular value in our array. 
    @param uint8_t r(red col 8 bit), uint8_t g(green col 8 bit), uint8_t b(blue col 8 bit), uin16_t led(position of LED in array)
*/
/**************************************************************************/
void UDPStripControl::set_led(uint8_t r, uint8_t g, uint8_t b, uint16_t led){
    // Don't wanna go out of bounds :0 and cause a segfault :(
    if(led < this->num_leds){
        this->data_arr[led * 3] = r;
        this->data_arr[led * 3 + 1] = g;
        this->data_arr[led * 3 + 2] = b;
    }
}

/**************************************************************************/
/*!
    @brief Sets all of our LEDs to a particular rgb value.  
    @param uint8_t r(red col 8 bit), uint8_t g(green col 8 bit), uint8_t b(blue col 8 bit)
*/
/**************************************************************************/
void UDPStripControl::set_strip(uint8_t r, uint8_t g, uint8_t b){
    for(uint16_t i = 0; i < this->num_leds; i++){
        this->set_led(r, g, b, i);
    }
}

