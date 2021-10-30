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

    tbip::Image Plot1(npx, npx, colors), Plot2(npx, npx, colors);
    tbip::cmap::Jet Cmap1(colors, 1., -1.);
    tbip::cmap::Viridis Cmap2(colors, 1., -1.);
    
    for(int r=0; r<npx; r++){
        double y = excursion - 2.*excursion*r/(npx-1);
        for(int c=0; c<npx; c++){
            double x = excursion - 2.*excursion*c/(npx-1);
            double f = function(x, y);
            Plot1.set_pixel(c, r, Cmap1(f));
            Plot2.set_pixel(c, r, Cmap2(f));
        }
    }

    Plot1.save("function_jet.ppm");
    Plot2.save("function_viridis.ppm");

    return 0;
}