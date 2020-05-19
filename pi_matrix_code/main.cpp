#include "led-matrix-c.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <unistd.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>

#include "pb.h"
#include "pb_common.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "messagedata.pb.h"


// Global variables for our udp server. 
// Preprocessor
#define MAXLINE 7000
const uint16_t SERVER_PORT = 4040; 
// Socket ID. 
int sockfd; 
// Socket address information
struct sockaddr_in servaddr, cliaddr; 
// UDP array that saves receive information
char udp_arr[7000];

void setup_matrix(void);
void setup_udp_server(void);  
void unpack_information(int len);
void update_matrix_information(void);

struct {
	// Global variables for matrix manipulation. 
	struct RGBLedMatrixOptions options;
	struct RGBLedMatrix *matrix;
	struct LedCanvas *offscreen_canvas;
	int width, height;
	uint8_t matrix_buffer_arr[7000]; 

}matrix_information;

int setup_matrix(int argc, char **argv){
  memset(&matrix_information.options, 0, sizeof(matrix_information.options));
  matrix_information.options.rows = 32;
  matrix_information.options.chain_length = 1;

  /* This supports all the led commandline options. Try --led-help */
  matrix_information.matrix = led_matrix_create_from_options(&matrix_information.options, &argc, &argv);
  if (matrix_information.matrix == NULL)
    return 1;

  /* Let's do an example with double-buffering. We create one extra
   * buffer onto which we draw, which is then swapped on each refresh.
   * This is typically a good aproach for animations and such.
   */
  matrix_information.offscreen_canvas = led_matrix_create_offscreen_canvas(matrix_information.matrix);
  led_canvas_get_size(matrix_information.offscreen_canvas, &matrix_information.width, &matrix_information.height);
  fprintf(stderr, "Size: %dx%d. Hardware gpio mapping: %s\n",
          matrix_information.width, matrix_information.height, matrix_information.options.hardware_mapping);	  
}

void setup_udp_server(void){
	// Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
	memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr));
	// Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(SERVER_PORT);
	// Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
}


void unpack_information(int len){
	if(len >= 16){
		// Message Decoding. 
		MessageData latest_message_data;
		//latest_message_data.message_type = 2;
		
		{
			uint8_t message_raw_dta[16]; 
			for(uint8_t i = 0; i < 16; i++)
				message_raw_dta[i] = udp_arr[i];
			pb_istream_t msg_in = pb_istream_from_buffer(message_raw_dta, 16);
			pb_decode(&msg_in, MessageData_fields, &latest_message_data);
		}
		if(latest_message_data.message_type == MessageData_MessageType_MATRIX_DATA)
			update_matrix_information();
	}
}


void update_matrix_information(void){
	// Copy values over!
	for(uint16_t i = 0; i < 6144; i++){
		matrix_information.matrix_buffer_arr[i] = udp_arr[i + 16];
	}
	uint32_t spot = 0; 

	// Then push them to led array!
	for (uint8_t y = 0; y < matrix_information.height; ++y) {
		for (uint8_t x = 0; x < matrix_information.width; ++x) {
		led_canvas_set_pixel(matrix_information.offscreen_canvas, x, y, matrix_information.matrix_buffer_arr[3 * spot], matrix_information.matrix_buffer_arr[3 * spot + 1], matrix_information.matrix_buffer_arr[3 * spot + 2]);
		spot++; 
		}
	}
	// Upload the frame. 
	matrix_information.offscreen_canvas = led_matrix_swap_on_vsync(matrix_information.matrix, matrix_information.offscreen_canvas);
}

int main(int argc, char **argv){
	
	setup_matrix(argc, argv);
	setup_udp_server();
	
	// Main loop that does everything
	while(1){
		int n; 
		socklen_t len;
		len = sizeof(cliaddr);  //len is value/resuslt 
		n = recvfrom(sockfd, (char *)udp_arr, MAXLINE,  
					MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
					&len); 
		
		if(len != 0){
			udp_arr[n] = '\0';
			unpack_information(n);
		}
	}
	// Let's prevent memory leaks. 
	led_matrix_delete(matrix_information.matrix);

  return 0;
}
