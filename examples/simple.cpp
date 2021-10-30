#include <iostream>
#include "tbip.h"

int main(){

    tbip::Image A(256, 256, 256);
    for(int r=0; r<256; r++){
        for(int c=0; c<256; c++){
            tbip::RGB color(r, c, 255);
            A.set_pixel(r, c, color);
        }
    }
    
    tbip::Image B = A;
    B.to_negative();

    tbip::Image C = A;
    C.to_grayscale();

    A.save("A.ppm");
    B.save("B.ppm");
    C.save("C.ppm");

    return 0;
}
