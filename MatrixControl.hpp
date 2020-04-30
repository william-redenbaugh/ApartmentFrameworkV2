#ifndef _MATRIX_CONTROL_HPP
#define _MATRIX_CONTROL_HPP

#include "udp_low.hpp"

class MatrixControl{
    public: 
        // Initializer for LED strip over udp communication
        void begin(const char *addr, uint16_t port, uint8_t x, uint8_t y);

        // Deconstructor so we don't leave any unallocated data. 
        void end(void);
    
        // Set the LED to a particular color. 
        void set_led(uint8_t r, uint8_t g, uint8_t b, uint8_t x, uint8_t y);

        // Push data up via UDP.
        void update(void);

    private: 
        uint8_t x, y;
        
        // Address information so we know where to send the data
        struct sockaddr_in led_strip_addr;
        // Pointer reference to the array with all the strip information
        uint8_t *data_arr;
        uint32_t arr_size; 

};

#endif 