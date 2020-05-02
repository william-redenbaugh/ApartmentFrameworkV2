#include "StripAnimations.hpp"
#include <thread>

void test_thread(StripAnimationHandler *self_ptr){
    self_ptr->strip_control_ptr->update();
}

/*
Function: begin(UDPStripControl *ptr)
Description: sets up the animation handle for strip control!
Parameters: A pointer reference to one of the UDPStripControl objects
Return: none
*/
void StripAnimationHandler::begin(UDPStripControl *ptr){
    this->strip_control_ptr = ptr; 
    std::thread  strip_control_thread(test_thread, this);
}