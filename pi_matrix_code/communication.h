#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

// Include our Standard c and c++ libraries
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Include our communication libraries. 
#include <unistd.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>

// Include our data serialization and deserialization libraries. 
#include "pb.h"
#include "pb_common.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "messagedata.pb.h"

void setup_udp_server(void);  
int read_udp_dat(void);
_MessageData_MessageType unpack_information(int len);
uint8_t* get_udp_arr_dat();

#endif