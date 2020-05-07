#include <iostream>
#include "UDPStripControl.h"
#include "HeartControl.hpp"
#include "ClockControl.hpp"
#include "MatrixControl.hpp"
#include "StripAnimations.hpp"

// Protobuffer stuff. 
#include "status.pb.h"
#include "messagedata.pb.h"
#include "pb.h"
#include "pb_encode.h"
#include "pb_decode.h"

// Cap N Proto Libraries.  Unnecesarry for now, but useful later perhaps?
#include <capnp/message.h>
#include <capnp/serialize-packed.h>

// Allows us to test and make sure protobuffers are working properly. 
void testing_protobuffers(void);

int main(void){
    // Test to make sure protobufffers work properly. 
    testing_protobuffers();

    // Remote control of strip testing. 
    UDPStripControl strip; 
    const char *strip_ip_addr = "192.168.1.2";
    strip.begin(strip_ip_addr, 5005, 20);
    strip.set_strip(100, 100, 100);
    strip.update();
    // Testing of the strip animation handler. 
    StripAnimationHandler strip_animations; 
    strip_animations.begin(&strip);

    // Remote control of heart testing 
    HeartControl heart; 
    const char *heart_ip_addr = "192.168.1.42";
    heart.begin(heart_ip_addr, 4250);
    heart.lamp_on();

    // Remote control of clock testing. 
    ClockControl clock; 
    const char *clock_ip_addr = "192.168.1.24";
    clock.begin(clock_ip_addr, 4210);
    clock.wake();

    // Remote control of matrix testing. 
    MatrixControl matrix_control; 
    const char *matrix_ip_addr = "192.168.1.39";
    matrix_control.begin(matrix_ip_addr, 4400, 64, 32);
    matrix_control.set_led(100, 100, 100, 1, 1);

    return 0;
}

void testing_protobuffers(void){
    BoardStatus board_status; 
    board_status.free_mem_kb = 500; 
    board_status.status = 1; 

    uint8_t buffer[128];
    size_t msg_len; 

    pb_ostream_t stream_out = pb_ostream_from_buffer(buffer, sizeof(buffer));
    pb_encode(&stream_out, BoardStatus_fields, &board_status);

    pb_istream_t stream_in  = pb_istream_from_buffer(buffer, msg_len);
    
    BoardStatus board_status_in; 
    pb_decode(&stream_in, BoardStatus_fields, &board_status_in);
}

void testing_message_size_pb(void){
    MessageData message_data_out;
    message_data_out.message_size = 230;
    message_data_out.message_type = MessageData_MessageType_MATRIX_DATA;

    // Put data into serialized format. 
    uint8_t buffer[32];
    pb_ostream_t msg_out = pb_ostream_from_buffer(buffer, sizeof(buffer));
    pb_encode(&msg_out, MessageData_fields, &message_data_out);

    // Unpack serialsed data. 
    pb_istream_t msg_in = pb_istream_from_buffer(buffer, 32);

    MessageData message_data_in; 
    pb_decode(&msg_in, MessageData_fields, &message_data_in);

    if(message_data_in.message_size == message_data_out.message_size && message_data_in.message_type == message_data_out.message_type){
        printf("Testing message data size succedded! \n");
    }
}