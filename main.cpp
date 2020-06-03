// Standard C++ files
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>

// Protobuffer stuff. 
#include "messagedata.pb.h"
#include "pb.h"
#include "pb_encode.h"
#include "pb_decode.h"

// Our Module files!
#include "UDPStripControl.h"
#include "HeartControl.hpp"
#include "ClockControl.hpp"
#include "MatrixControl.hpp"
#include "StripAnimations.hpp"

// Low Level files 
#include "udp_low.hpp"

void testing_message_size_pb(void);
void test_matrix_fill(MatrixControl *matrix);
void test_matrix_hsv_animation(MatrixControl *matrix);

int main(void){
    // Opens up a UDP server.
    udp_server_socket_open(4040);
    
    // Matrix controller object. 
    MatrixControl matrix_control;
    
    const char *ip_addr = "192.168.1.20";
    matrix_control.begin(ip_addr, 4040, 64, 32);
    
    while(1)
        test_matrix_hsv_animation(&matrix_control);

    return 0;
}

/**************************************************************************/
/*!
    @brief Quick test of our matrix that allows us to test filling it up. 
*/
/**************************************************************************/
void test_matrix_fill(MatrixControl *matrix){
    // Quick test by filling in the box of one of our matrices. 
    for(uint8_t y = 0; y < 32; y++){
        for(uint8_t x = 0; x < 64; x++){
            matrix->set_led(100, 100, 100, x, y);
            matrix->update();
            usleep(10000);
        }
    }
}

/**************************************************************************/
/*!
    @brief Allows us to quickly test the hsv functionality of our matrix animation handler. 
*/
/**************************************************************************/
void test_matrix_hsv_animation(MatrixControl *matrix){
    for(uint8_t h = 0; h < 255; h++){
        for(uint8_t y = 0; y < 32; y++){
            for(uint8_t x = 0; x < 64; x++){
                uint8_t hue_val = (uint8_t)((y * x)/5 + h * 3) % 255; 
                matrix->set_led_hsv(hue_val, 255, 20, x, y);
            }
        }
        matrix->update();
        usleep(10000);
    }
}

/**************************************************************************/
/*!
    @brief Tests our MessageData Data serialization an deserialization data. 
*/
/**************************************************************************/
void testing_message_size_pb(void){
    // Generate a message and populate data. 
    MessageData message_data_out;
    message_data_out.message_size = 230;
    message_data_out.message_type = MessageData_MessageType_MATRIX_DATA;

    // Put data into serialized format. 
    uint8_t buffer[32];
    pb_ostream_t msg_out = pb_ostream_from_buffer(buffer, sizeof(buffer));
    pb_encode(&msg_out, MessageData_fields, &message_data_out);

    // Unpack serialsed data. 
    pb_istream_t msg_in = pb_istream_from_buffer(buffer, 32);

    // Save copy of deserialized data
    MessageData message_data_in; 
    pb_decode(&msg_in, MessageData_fields, &message_data_in);

    // Check to make sure that data was unpacked properly. 
    if(message_data_in.message_size == message_data_out.message_size && message_data_in.message_type == message_data_out.message_type)
        printf("Testing message data size succedded! \n");
}
