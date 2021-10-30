#include <iostream>
#include <fstream>
#include <cmath>
#include "tbip.h"
#include "tbip_colormaps.h"

double function(double x, double y){
    return sin(x*y);
}

int main(){

    double excursion = 5.;
    double npx = 1000;
    int colors = 1000;

    tbip::Image Plot(npx, npx, colors);
    tbip::cmap::Jet MyCmap(colors, 1., -1.);
    
    for(int r=0; r<npx; r++){
        double y = excursion - 2.*excursion*r/(npx-1);
        for(int c=0; c<npx; c++){
            double x = excursion - 2.*excursion*c/(npx-1);
            double f = function(x, y);
            Plot.set_pixel(c, r, MyCmap(f));
        }
    }

    Plot.save("function.ppm");

    return 0;
}