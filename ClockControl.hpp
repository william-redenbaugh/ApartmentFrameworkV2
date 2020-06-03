#ifndef _CLOCKCONTROL_HPP
#define _CLOCKCONTROL_HPP

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

/**************************************************************************/
/*!
    @brief UDP Message Handler for controlling our clock. 
*/
/**************************************************************************/
class ClockControl{
    public: 
    void begin(const char *addr, uint16_t port);
    
    // Remote turn on and off of the clock.
    void sleep(void);
    void wake(void);
    
    private:
    
    // IP address to send information to the clock
    struct sockaddr_in clock_addr;
    
};

#endif 