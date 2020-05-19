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
  
	  
// Global variables for matrix manipulation. 
struct RGBLedMatrixOptions options;
struct RGBLedMatrix *matrix;
struct LedCanvas *offscreen_canvas;
int width, height;
int x, y, i;
uint8_t matrix_buffer_arr[7000]; 

void setup_matrix(int argc, char **argv){
  memset(&options, 0, sizeof(options));
  options.rows = 32;
  options.chain_length = 1;

  /* This supports all the led commandline options. Try --led-help */
  matrix = led_matrix_create_from_options(&options, &argc, &argv);
  if (matrix == NULL)
    return 1;

  /* Let's do an example with double-buffering. We create one extra
   * buffer onto which we draw, which is then swapped on each refresh.
   * This is typically a good aproach for animations and such.
   */
  offscreen_canvas = led_matrix_create_offscreen_canvas(matrix);
  led_canvas_get_size(offscreen_canvas, &width, &height);
  fprintf(stderr, "Size: %dx%d. Hardware gpio mapping: %s\n",
          width, height, options.hardware_mapping);	  
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

int main(int argc, char **argv) {
	
	// Setup matrix command
	setup_matrix(argc, argv);
	setup_udp_server();
	
	// Main loop that does everything
	while(1){
		uint32_t spot = 0; 
		
		int len, n; 
  
		len = sizeof(cliaddr);  //len is value/resuslt 
	  
		n = recvfrom(sockfd, (char *)udp_arr, MAXLINE,  
					MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
					&len); 
		
		if(len != 0){
			
			// Copy values over!
			for(uint16_t i = 0; i < 6144; i++){
				matrix_buffer_arr[i] = udp_arr[i];
			}
			udp_arr[n] = '\0';
			
			// Then push them to led array!
			for (y = 0; y < height; ++y) {
			  for (x = 0; x < width; ++x) {
				led_canvas_set_pixel(offscreen_canvas, x, y, matrix_buffer_arr[3 * spot], matrix_buffer_arr[3 * spot + 1], matrix_buffer_arr[3 * spot + 2]);
				spot++; 
			  }
			}
			// Upload the frame. 
			offscreen_canvas = led_matrix_swap_on_vsync(matrix, offscreen_canvas);
		}
	}
	// Let's prevent memory leaks. 
	led_matrix_delete(matrix);

  return 0;
}
