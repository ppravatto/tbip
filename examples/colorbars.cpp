#include <iostream>
#include "tbip.h"
#include "tbip_colormaps.h"

int main(){

    const int ncolors = 1024;
    const int width = 1100;
    const int height = 260;

    tbip::Image MyPlot(width, height, ncolors);
    
    tbip::cmap::Jet jet(ncolors, 1000., 0.);
    tbip::cmap::Inferno inferno(ncolors, 1000., 0.);
    tbip::cmap::Viridis viridis(ncolors, 1000., 0.);
    tbip::cmap::Plasma plasma(ncolors, 1000., 0.);
    tbip::cmap::Magma magma(ncolors, 1000., 0.);

    MyPlot.fill(ncolors-1, ncolors-1, ncolors-1);

    for(int x=0; x<=(width-100); x++){
        for(int y=0; y<40; y++){
            MyPlot.set_pixel(50+x, 10+y, jet(x));
            MyPlot.set_pixel(50+x, 60+y, inferno(x));
            MyPlot.set_pixel(50+x, 110+y, viridis(x));
            MyPlot.set_pixel(50+x, 160+y, plasma(x));
            MyPlot.set_pixel(50+x, 210+y, magma(x));
        }
    }

    MyPlot.save("colorbars.ppm");

    return 0;
}