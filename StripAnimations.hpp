#ifndef _STRIP_ANIMATIONS_HPP
#define _STRIP_ANIMATIONS_HPP

#include "UDPStripControl.h"
#include <iostream>

class StripAnimationHandler{

    public: 
        void begin(UDPStripControl *ptr);
        
        UDPStripControl *strip_control_ptr;
};

#endif 