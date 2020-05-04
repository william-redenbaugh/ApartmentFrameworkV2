#include <iostream>
#include "UDPStripControl.h"
#include "HeartControl.hpp"
#include "ClockControl.hpp"
#include "MatrixControl.hpp"
#include "StripAnimations.hpp"

// Cap N Proto Libraries.  Unnecesarry for now, but useful later perhaps?
#include <capnp/message.h>
#include <capnp/serialize-packed.h>

int main(void){
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
}