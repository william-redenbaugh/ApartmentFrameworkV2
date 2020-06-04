#include "proto_handler.h"

void testing_message_size_pb(void);

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
