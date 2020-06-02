#include "matrix.h"

int setup_matrix(int argc, char **argv);
void update_matrix_information(uint8_t *udp_arr);
void free_matrix_mem(void);

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

  matrix_information.matrix = led_matrix_create_from_options(&matrix_information.options, &argc, &argv);
  if (matrix_information.matrix == NULL)
    return 1;

  matrix_information.offscreen_canvas = led_matrix_create_offscreen_canvas(matrix_information.matrix);
  led_canvas_get_size(matrix_information.offscreen_canvas, &matrix_information.width, &matrix_information.height);
  fprintf(stderr, "Size: %dx%d. Hardware gpio mapping: %s\n",
          matrix_information.width, matrix_information.height, matrix_information.options.hardware_mapping);	  
}

void update_matrix_information(uint8_t *udp_arr){
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

void free_matrix_mem(void){
    // Let's prevent memory leaks. 
	led_matrix_delete(matrix_information.matrix);
}