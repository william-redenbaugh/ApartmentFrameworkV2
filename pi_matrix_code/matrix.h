#ifndef _MATRIX_H
#define _MATRIX_H


// Our LED matrix driver stuff!
#include "led-matrix-c.h"

// Our C and C++ library stuff!
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Include our Standard c and c++ libraries
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Include our LED matrix drivers.
#include "led-matrix-c.h"

int setup_matrix(int argc, char **argv);
void update_matrix_information(uint8_t *udp_arr);
void free_matrix_mem(void);

#endif