#include "matrix_animations.h"

void test_matrix_fill(MatrixControl *matrix, volatile bool *interrupt);
void test_matrix_hsv_animation(MatrixControl *matrix, volatile bool *interrupt);
void fade(MatrixControl *matrix, RgbColor col, volatile bool *interrupt); 
void fade_hsv(MatrixControl *matrix, HsvColor col, volatile bool *interrupt);

/**************************************************************************/
/*!
    @brief Quick test of our matrix that allows us to test filling it up. 
*/
/**************************************************************************/
void test_matrix_fill(MatrixControl *matrix, volatile bool *interrupt){
    // Quick test by filling in the box of one of our matrices. 
    for(uint8_t y = 0; y < 32; y++){
        for(uint8_t x = 0; x < 64; x++){
            
            // If animation needs to be interrupted we can interrupt here. 
            if(*interrupt)
                return; 
            matrix->set_led(100, 100, 100, x, y);
            matrix->update();
            usleep(10000);
        }
    }
}

/**************************************************************************/
/*!
    @brief Allows us to quickly test the hsv functionality of our matrix animation handler. 
*/
/**************************************************************************/
void test_matrix_hsv_animation(MatrixControl *matrix, volatile bool *interrupt){
    for(uint8_t h = 0; h < 255; h++){
        for(uint8_t y = 0; y < 32; y++){
            for(uint8_t x = 0; x < 64; x++){
                uint8_t hue_val = (uint8_t)((y * x) + h * 3) % 255; 
                matrix->set_led_hsv(hue_val, 255, 50, x, y);
            }
        }

        // If animation needs to be interrupted, we can end it right here. 
        if(*interrupt)
            return;

        matrix->update();
        usleep(10000);
    }
}

void fade(MatrixControl *matrix, RgbColor col, volatile bool *interrupt){
    HsvColor hsv = RgbToHsv(col);

    while(1){
        uint16_t num_complete = 0; 

        for(uint8_t x = 0; x < 64; x++){
            for(uint8_t y = 0; y < 32; y++){
                HsvColor hsv_buff = matrix->return_hsv(x, y);          
                uint8_t col_complete = 0; 

                // increment
                if(hsv_buff.h > hsv.h)
                    hsv_buff.h--;
                else if(hsv_buff.h < hsv.h)
                    hsv_buff.h++;
                else
                    col_complete++;
                if(hsv_buff.s > hsv.s)
                    hsv_buff.s--;
                else if(hsv_buff.s < hsv.s)
                    hsv_buff.s++;
                else
                    col_complete++;
                if(hsv_buff.v > hsv.v)
                    hsv_buff.v--;
                else if(hsv_buff.v < hsv.v)
                    hsv_buff.v++;
                else
                    col_complete++;
                
            }
        }
        if(x_complete == 64 && y_complete == 64)
            break;
    }
}

void fade_hsv(MatrixControl *matrix, HsvColor col, volatile bool *interrupt){

}