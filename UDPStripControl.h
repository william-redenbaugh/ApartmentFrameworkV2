#ifndef _UDPSTRIPCONTROL_H
#define _UDPSTRIPCONTROL_H

// Default Socket and C++ libraries
#include <iostream>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

// Tiny little UDP wrappper that simplifies some things. 
#include "udp_low.hpp"

class UDPStripControl{
    public:
    // Initializer for LED strip over udp communication
    void begin(const char *addr, uint16_t port, uint16_t num_leds);
    
    // Actually involves sending the information
    void update(void);

    // Manipulation of LED information
    void set_led(uint8_t r, uint8_t g, uint8_t b, uint16_t led);
    
    private:
    
    // Address information so we know where to send the data
    struct sockaddr_in led_strip_addr;
    // Pointer reference to the array with all the strip information
    uint8_t *data_arr;
    uint16_t arr_size; 
    uint16_t num_leds; 
};

#endif