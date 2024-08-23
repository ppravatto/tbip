#include "tbip_colormaps.h"
#include "tbip_exceptions.h"

#include <cmath>
#include <vector>

namespace tbip{

    namespace cmap{

        namespace _inferno_{

            const std::vector<double> r = {0.0002167321444, 0.105439129, 11.48547075, -41.28337112, 76.3846731, -70.60010305, 24.87765459};
            const std::vector<double> g = {0.001634352657, 0.5582683924, -3.932783903, 17.26053599, -33.06546395, 32.29699895, -12.11918983};
            const std::vector<double> b = {0., 3.893047193, -15.78159969, 43.90679088, -80.98220367, 72.47113126, -22.83763853};

        }

        namespace _viridis_{
            
            const std::vector<double> r = {0.2777273272, 0.1050930431, -0.3308618287, -4.634230499, 6.228269936, 4.776384998, -5.435455856};
            const std::vector<double> g = {0.005407344545, 1.40461353, 0.2148475595, -5.799100973, 14.17993337, -13.74514538, 4.645852612};
            const std::vector<double> b = {0.3340998053, 1.384590163, 0.09509516303, -19.33244096, 56.6905526, -65.35303263, 26.31243525};

        }

        namespace _plasma_{

            const std::vector<double> r = {0.05873234392,2.176514634,-2.689460476,6.130348346,-11.10743619,10.02306558,-3.658713843};
            const std::vector<double> g = {0.02643670893,0.2383834171,-7.455851136,42.34618815,-82.66631109,71.4136177,-22.93153465};
            const std::vector<double> b = {0.544,0.75396046,3.11079994,-28.51885465,60.13984767,-54.07218656,18.19190779};

        }

        namespace _magma_{

            const std::vector<double> r = {0.0009989012087,0.249495333,8.281844537,-27.43068005,51.7272328,-50.33172903,18.49519728};
            const std::vector<double> g = {0.0009989012087,0.6716940479,-3.546937947,14.14200155,-27.70318812,28.79667521,-11.39091914};
            const std::vector<double> b = {0.0009989012087,2.472568783,0.3117623206,-13.53177967,12.8328019,4.19772368,-5.553764004};

        }

        static double compute_polynomial(double x, std::vector<double> coeff){
            double y = 0.;
            for(int i=0; i<int(coeff.size()); i++){
                y += coeff[i]*pow(x, i);
            }
            return y;
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


        //Define members of the Inferno class

        Inferno::Inferno(int colors_, double max_, double min_, bool reverse_) : Colormap(colors_, max_, min_, reverse_) {}
        Inferno::Inferno(int colors_, double max_, double min_) : Colormap(colors_, max_, min_) {}

        RGB Inferno::operator() (double value){
            if(value<min || value>max) throw _exceptions_::ValueError();
            double x = (value-min)/(max-min);
            if(reverse == true) x = 1.-x;
            double r = max_color * compute_polynomial(x, _inferno_::r);
            double g = max_color * compute_polynomial(x, _inferno_::g);
            double b = max_color * compute_polynomial(x, _inferno_::b);
            RGB color(r, g, b);
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

        //Define members of the Plasma class

        Plasma::Plasma(int colors_, double max_, double min_, bool reverse_) : Colormap(colors_, max_, min_, reverse_) {}
        Plasma::Plasma(int colors_, double max_, double min_) : Colormap(colors_, max_, min_) {}

        RGB Plasma::operator() (double value){
            if(value<min || value>max) throw _exceptions_::ValueError();
            double x = (value-min)/(max-min);
            if(reverse == true) x = 1.-x;
            double r = max_color * compute_polynomial(x, _plasma_::r);
            double g = max_color * compute_polynomial(x, _plasma_::g);
            double b = max_color * compute_polynomial(x, _plasma_::b);
            RGB color(r, g, b);
            return color;
        }

        //Define members of the Magma class

        Magma::Magma(int colors_, double max_, double min_, bool reverse_) : Colormap(colors_, max_, min_, reverse_) {}
        Magma::Magma(int colors_, double max_, double min_) : Colormap(colors_, max_, min_) {}

        RGB Magma::operator() (double value){
            if(value<min || value>max) throw _exceptions_::ValueError();
            double x = (value-min)/(max-min);
            if(reverse == true) x = 1.-x;
            double r = max_color * compute_polynomial(x, _magma_::r);
            double g = max_color * compute_polynomial(x, _magma_::g);
            double b = max_color * compute_polynomial(x, _magma_::b);
            RGB color(r, g, b);
            return color;
        }


    }

}