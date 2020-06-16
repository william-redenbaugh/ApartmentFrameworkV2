#include "StripAnimations.hpp"
#include <thread>

/**************************************************************************/
/*!
    @brief Runs update in test thread. 
*/
/**************************************************************************/
void test_thread(StripAnimationHandler *self_ptr){
    self_ptr->strip_control_ptr->update();
}

/*
/**************************************************************************/
/*!
    @brief Sets up strip animation handler with designated strip. 
    @param UDPStripControl *ptr(pointer to strip)
*/
/**************************************************************************/
void StripAnimationHandler::begin(UDPStripControl *ptr){
    this->strip_control_ptr = ptr; 
    std::thread  strip_control_thread(test_thread, this);
}