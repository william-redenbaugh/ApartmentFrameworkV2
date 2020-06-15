#ifndef _UDPLOW_HPP
#define _UDPLOW_HPP

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

/**************************************************************************/
/*!
    @brief UDP wrapper that allows us to encapsulate all of UDP server's functions into something a little easier to use. 
*/
/**************************************************************************/
class UDPWrapper{
    public: 
        void open(uint16_t port, uint16_t maxline);
        uint16_t receive_blocking(uint8_t *array);
        void send(uint16_t packet_size, uint8_t *array);
        void send_ip(uint16_t packet_size, uint8_t *array, struct sockaddr_in *rec_sock);
    
        private: 
        // Address handler that we use to manage our ports. 
        struct sockaddr_in server_address; 
        struct sockaddr_in client_address; 
        
        // Socket ID Handlers
        int server_socket_fd = 0;

        uint16_t maxline = 2048;
};

#endif