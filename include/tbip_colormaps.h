#ifndef TBIP_CMAP_H
#define TBIP_CMAP_H

#include "tbip.h"

namespace tbip{

    namespace cmap{

        class Colormap{
            protected:
                bool reverse;
                int num_color, max_color;
                double max, min;
            public:
                Colormap(int colors_, double max_, double min_, bool reverse_);
                Colormap(int colors_, double max_, double min_);                
                virtual RGB operator() (double value) = 0;
        };

        class Jet final : public Colormap{
            public:
                Jet(int colors_, double max_, double min_, bool reverse_);
                Jet(int colors_, double max_, double min_);
                RGB operator() (double value);
        };

    }

}

#endif