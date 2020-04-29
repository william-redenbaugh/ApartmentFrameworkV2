#ifndef _UDP_LOW_HPP
#define _UDP_LOW_HPP

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

// C function that opens a udp socket. 
void udp_server_socket_open(uint16_t port);

// C function that waits for a packet to come in, and sets a pointer reference to an array. 
uint16_t udp_server_receive_blocking(uint8_t *array);

// C function that allows us to send out data. It sends out the data to the last device that sent it data. 
void udp_server_send(uint16_t packet_size, uint8_t *array);

// C function that allows us to send out data. It sends out the data to the any desired device
void udp_server_sendto(uint16_t packet_size, uint8_t *array, struct sockaddr_in *rec_sock);
#endif 