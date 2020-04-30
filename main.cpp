#include <iostream>
#include "UDPStripControl.h"
#include "HeartControl.hpp"
#include "ClockControl.hpp"

// Cap N Proto Libraries.  Unnecesarry for now, but useful later perhaps?
#include <capnp/message.h>
#include <capnp/serialize-packed.h>

int main(void){
    UDPStripControl strip; 
    const char *strip_ip_addr = "192.168.1.2";
    
    strip.begin(strip_ip_addr, 5005, 20);
    strip.update();

    HeartControl heart; 
    const char *heart_ip_addr = "192.168.1.42";
    heart.begin(heart_ip_addr, 4250);
    heart.lamp_on();

    ClockControl clock; 
    const char *clock_ip_addr = "192.168.1.24";
    clock.begin(clock_ip_addr, 4210);
    clock.wake();
}