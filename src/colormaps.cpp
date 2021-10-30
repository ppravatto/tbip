#include "tbip_colormaps.h"
#include "tbip_exceptions.h"

namespace tbip{

    namespace cmap{

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

    }

}