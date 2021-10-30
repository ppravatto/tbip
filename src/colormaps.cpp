#include "tbip_colormaps.h"
#include "tbip_exceptions.h"

#include <cmath>
#include <vector>

namespace tbip{

    namespace cmap{

        double compute_polynomial(double x, std::vector<double> coeff){
            double y = 0.;
            for(int i=0; i<coeff.size(); i++){
                y += coeff[i]*pow(x, i);
            }
            return y;
        }

        namespace _viridis_{
            
            const std::vector<double> r {0.2777273272234177, 0.1050930431085774, -0.3308618287255563, -4.634230498983486, 6.228269936347081, 4.776384997670288, -5.435455855934631};
            const std::vector<double> g {0.005407344544966578, 1.404613529898575, 0.214847559468213, -5.799100973351585, 14.17993336680509, -13.74514537774601, 4.645852612178535};
            const std::vector<double> b {0.3340998053353061, 1.384590162594685, 0.09509516302823659, -19.33244095627987, 56.69055260068105, -65.35303263337234, 26.3124352495832};

        }


        //Define members of the Colormap abstract base class

        Colormap::Colormap(int colors_, double max_, double min_, bool reverse_) : reverse(reverse_), num_color(colors_), max_color(colors_-1), max(max_), min(min_){
            if(min >= max || colors_ <= 0) throw _exceptions_::InitValError();
        }

        Colormap::Colormap(int colors_, double max_, double min_) : Colormap(colors_, max_, min_, false) {}


        //Define members of the Jet class

        Jet::Jet(int colors_, double max_, double min_, bool reverse_) : Colormap(colors_, max_, min_, reverse_) {}
        Jet::Jet(int colors_, double max_, double min_) : Colormap(colors_, max_, min_) {}

        RGB Jet::operator() (double value){
            if(value<min || value>max) throw _exceptions_::ValueError();
            const double m = 1./8., c = 1./2.;
            RGB color;
            double x = 32.*(value-min)/(max-min);
            if(reverse == true) x = 32.-x;

            if(x<=4.) color.set(0, 0, int(max_color*(m*x+c)));
            else if(x<=12.) color.set(0, int(max_color*m*(x-4.)), max_color);
            else if(x<=20.) color.set(int(max_color*m*(x-12.)), max_color, int(max_color*(1.-m*(x-12.))));
            else if(x<=28.) color.set(max_color, int(max_color*(1.-m*(x-20.))), 0);
            else if(x<=32.) color.set(int(max_color*(1.-m*(x-28.))), 0, 0);
            else throw _exceptions_::ValueError();
            return color;
        }

        //Define members of the Viridis class

        Viridis::Viridis(int colors_, double max_, double min_, bool reverse_) : Colormap(colors_, max_, min_, reverse_) {}
        Viridis::Viridis(int colors_, double max_, double min_) : Colormap(colors_, max_, min_) {}

        RGB Viridis::operator() (double value){
            if(value<min || value>max) throw _exceptions_::ValueError();
            double x = (value-min)/(max-min);
            if(reverse == true) x = 1.-x;
            double r = max_color * compute_polynomial(x, _viridis_::r);
            double g = max_color * compute_polynomial(x, _viridis_::g);
            double b = max_color * compute_polynomial(x, _viridis_::b);
            RGB color(r, g, b);
            return color;
        }

    }

}