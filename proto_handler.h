#ifndef _PROTO_HANDLER_H
#define _PROTO_HANDLER_H

// Standard C++ files
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>

// Protobuffer stuff. 
#include "messagedata.pb.h"
#include "pb.h"
#include "pb_encode.h"
#include "pb_decode.h"

void testing_message_size_pb(void);

#endif 