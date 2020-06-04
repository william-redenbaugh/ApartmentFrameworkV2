#ifndef _MATRIX_ANIMATIONS_H
#define _MATRIX_ANIMATIONS_H
#include "MatrixControl.hpp"

void test_matrix_fill(MatrixControl *matrix, volatile bool *interrupt);
void test_matrix_hsv_animation(MatrixControl *matrix, volatile bool *interrupt);
void fade_red(MatrixControl *matrix, RgbColor col, volatile bool *interrupt);
void fade_hsv(MatrixControl *matrix, HsvColor col, volatile bool *interrupt);

#endif 