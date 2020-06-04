#include "MatrixControl.hpp"

/**************************************************************************/
/*!
    @brief Allows us to setup the udp communication to our RGB LED matrix. 
    @param const char *addr(the string of the ip address), uint16_t port(port of device), uint8_t x, uint8_t y(device x and y pixel matrix size)
*/
/**************************************************************************/
void MatrixControl::begin(const char *addr, uint16_t port, uint8_t x, uint8_t y){
    this->led_strip_addr.sin_family = AF_INET; 
    this->led_strip_addr.sin_port = htons(port);
    this->led_strip_addr.sin_addr.s_addr = inet_addr(addr);

    // Generate array on heap that holds all of our matrix information
    this->data_arr = new uint8_t[x * y * 3 + 16];
    
    // Set the size of our array. 
    this->arr_size = x * y * 3 + 16;
    
    // Clears our the data. 
    memset(this->data_arr, 0, x*y*3+16);

    {
    // Generates the signature message that tells the device
    // on the other side that they are getting matrix data. 
    uint8_t buffer[16];
    // Message struct. 
    MessageData message_data_out;
    // Populate message data fields  
    message_data_out.message_size = x * y * 3;
    message_data_out.message_type = MessageData_MessageType_MATRIX_DATA;
    // Serialize into buffer
    pb_ostream_t msg_out = pb_ostream_from_buffer(buffer, sizeof(buffer));
    pb_encode(&msg_out, MessageData_fields, &message_data_out);
    // Copy buffer over to the main array buffer. 
    for(uint8_t i = 0; i < 16; i++)
        this->data_arr[i] = buffer[i];
    }

    // Set x and y size. 
    this->x = x; 
    this->y = y; 

    // Clear display. 
    this->update();
}

/**************************************************************************/
/*!
    @brief de allocates the array that we keep all our matrix UDP data in.
*/
/**************************************************************************/
void MatrixControl::end(void){
    //delete[] this->data_arr;
}

/**************************************************************************/
/*!
    @brief changes the udp buffer to represent change in the led pixel we want to see
    @param uint8_t r, uint8_t g, uint8_t b,(pixel rgb color value) uint8_t x, uint8_t y
*/
/**************************************************************************/
void MatrixControl::set_led(uint8_t r, uint8_t g, uint8_t b, uint8_t x, uint8_t y){
    // If pixels are out of bounds... 
    if(x > this->x & y > this->y)
        return; 

    // Figuring out where to put the data into the data array. 
    uint32_t spot = (y * this->x + x) * 3; 
    this->data_arr[spot + 16] = r; 
    this->data_arr[spot + 17] = g; 
    this->data_arr[spot+ 18] = b; 
}

/**************************************************************************/
/*!
    @brief changes the udp buffer to represent change in the led pixel we want to see with hsv data. 
    @param uint8_t h(hue value), uint8_t s(saturation value),  uint8_t v(value), uint8_t x(x pos), uint8_t y(y pos)
*/
/**************************************************************************/
void MatrixControl::set_led_hsv(uint8_t h, uint8_t s, uint8_t v, uint8_t x, uint8_t y){  
    HsvColor hsv = {h, s, v};
    RgbColor rgb = HsvToRgb(hsv);
    this->set_led((uint8_t)rgb.r , (uint8_t)rgb.g, (uint8_t)rgb.b, x, y);
}

/**************************************************************************/
/*!
    @brief Sends the UDP array buffer to the desired device. 
*/
/**************************************************************************/
void MatrixControl::update(void){
    // Sending over information via udp
    udp_server_sendto(this->arr_size, this->data_arr, &this->led_strip_addr);
}