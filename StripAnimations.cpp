#include "StripAnimations.hpp"
#include <thread>

void test_thread(StripAnimationHandler *self_ptr){
    self_ptr->strip_control_ptr->update();
}

void StripAnimationHandler::begin(UDPStripControl *ptr){
    this->strip_control_ptr = ptr; 
    std::thread  strip_control_thread(test_thread, this);
}