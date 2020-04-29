#ifndef _HEARTCONTROL_HPP
#define _HEARTCONTROL_HPP

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

class HeartControl{
    public:
    // Initialization command
    void begin(const char *addr, uint16_t port);

    // So we can remote lock/unlock the heart for authentication
    void lock(void);
    void unlock(void);

    // Remote control of the lampp
    void toggle_lamp(void);
    void lamp_on(void);
    void lamp_off(void);

    // Make the lamp beep :)
    void beep(void);

    private: 

    // IP address information to send message to heart. 
    struct sockaddr_in heart_addr;
    
};

#endif 