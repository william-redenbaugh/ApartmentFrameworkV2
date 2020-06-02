// Include our Standard c and c++ libraries
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Include our LED matrix drivers.
#include "led-matrix-c.h"
#include "matrix.h"

// Include our udp communcation stuff here. 
#include "communication.h"

int main(int argc, char **argv){	
	setup_matrix(argc, argv);
	setup_udp_server();
	
	while(1){
		int len = read_udp_dat();
		
		if(len != 0){
        	switch(unpack_information(len)){
				case(MessageData_MessageType_MATRIX_DATA):
				uint8_t *arr_ptr = get_udp_arr_dat();
				update_matrix_information(arr_ptr);
				break;
			}
    	}
		
	}

  return 0;
}
