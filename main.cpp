// Standard C++ files
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>


// Our Module files!
#include "UDPStripControl.h"
#include "HeartControl.hpp"
#include "ClockControl.hpp"
#include "MatrixControl.hpp"
#include "StripAnimations.hpp"

#include "matrix_animations.h"
#include "proto_handler.h"

// Low Level files 
#include "udp_low.hpp"

int main(void){
    // Opens up a UDP server.
    udp_server_socket_open(4040);
    
    // Matrix controller object. 
    MatrixControl matrix_control;
    
    const char *ip_addr = "192.168.1.20";
    matrix_control.begin(ip_addr, 4040, 64, 32);
    
    bool interrupt = false; 
    while(1)
        test_matrix_hsv_animation(&matrix_control, &interrupt);

    return 0;
}