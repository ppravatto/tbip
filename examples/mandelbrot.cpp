#include <iostream>
#include <fstream>
#include <complex>
#include <cmath>
#include <omp.h>
#include "tbip.h"
#include "tbip_colormaps.h"

const int max_iter = 400;

int get_convergence(std::complex<double> c){
    int iter=0;
    std::complex<double> z(0., 0.);
    while (iter < max_iter && std::abs(z) < 2.){
        z = std::pow(z, 2.) + c;
        iter++;
    }
    return iter;
}


int main(){

    int npx = 4000;
    int colors = 1000;

    tbip::Image Plot(npx, npx, colors);
    tbip::cmap::Jet cmap(colors, max_iter, 0., true);
    
    #pragma omp parallel for collapse(2) schedule(dynamic, 10)
    for(int r=0; r<npx; r++){
        for(int c=0; c<npx; c++){
            double x = -0.746 + 0.03*c/(npx-1.);
            double y = 0.245 - 0.04*r/(npx-1.);
            std::complex<double> p(x, y);
            int iter = get_convergence(p);
            Plot.set_pixel(c, r, cmap(iter));
        }
    }
    
    Plot.save("mandelbrot.ppm");

    return 0;
}