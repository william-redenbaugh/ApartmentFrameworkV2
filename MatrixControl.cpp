#include "MatrixControl.hpp"

/*
Function:begin(const char *addr, uint16_t port, uint8_t x, uint8_t y) 
Description: Allows us to setup the udp communication to our RGB LED matrix. 
Parameters: const char *addr(the string of the ip address), uint16_t port(port of device), uint8_t x, uint8_t y(device x and y pixel matrix size)
Returns: none
*/
void MatrixControl::begin(const char *addr, uint16_t port, uint8_t x, uint8_t y){
    this->led_strip_addr.sin_family = AF_INET; 
    this->led_strip_addr.sin_port = htons(port);
    this->led_strip_addr.sin_addr.s_addr = inet_addr(addr);

    this->data_arr = new uint8_t[x * y * 3 + 100];
    this->arr_size = x * y * 3 + 100;
    this->x = x; 
    this->y = y; 

    for(uint32_t i = 0; i < x * y * 3 + 100; i++){
        this->data_arr[i] = 0; 
    }
    
    this->update();
}

/*
Function: end(void)
Description: de allocates the array that we keep all our matrix UDP data in. 
Parameters: none
Returns: none
*/
void MatrixControl::end(void){
    delete[] this->data_arr;
}

/*
Function: set_led(uint8_t r, uint8_t g, uint8_t b, uint8_t x, uint8_t y)
Description: changes the udp buffer to represent change in the led pixel we want to see
Parameters:uint8_t r, uint8_t g, uint8_t b,(pixel rgb color value) uint8_t x, uint8_t y(pixel position)
Returns: none
*/
void MatrixControl::set_led(uint8_t r, uint8_t g, uint8_t b, uint8_t x, uint8_t y){
    // If pixels are out of bounds... 
    if(x > this->x & y > this->y)
        return; 

    // Figuring out where to put the data into the data array. 
    uint32_t spot = (y * this->x + x) * 3; 
    this->data_arr[spot] = r; 
    this->data_arr[spot + 1] = g; 
    this->data_arr[spot+ 2] = b; 
}

/*
Function: update(void)
Description: Sends the UDP array buffer to the desired device. 
Parameters:none
Returns: none
*/
void MatrixControl::update(void){
    // Sending over information via udp
    udp_server_sendto(this->arr_size, this->data_arr, &this->led_strip_addr);
}