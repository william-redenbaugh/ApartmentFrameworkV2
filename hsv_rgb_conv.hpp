#ifndef _HSV_RGB_CONV_HPP
#define _HSV_RGB_CONV_HPP

typedef struct {
    double r;       
    double g;       
    double b;       
} rgb;

typedef struct {
    double h;       
    double s;       
    double v;       
} hsv;

hsv rgb2hsv(rgb in);
rgb hsv2rgb(hsv in);

#endif 
