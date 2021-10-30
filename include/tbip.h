#ifndef TBIP_H
#define TBIP_H

#include <string>

namespace tbip{

    const int MAXVAL_PPM = 65536;

    struct RGB{
        int r, g, b;
        RGB();
        RGB(int r_, int g_, int b_);
        void set(int r_, int g_, int b_);
        RGB get_graylevel();
    };

    class Image{
        private:
            bool init;
            int width, height, max;
            RGB *data;
            void copy(const Image& source);
            void check_init();
            void check_color(RGB color);
            void check_pixel(int x, int y);

        public:
            Image();
            Image(int width_, int height_, int max_);
            Image(int width_, int height_, int max_, RGB* data_);
            Image(const Image& source);
            ~Image();
            Image& operator= (const Image& source);
            void save(std::string filename);
            void set_pixel(int x, int y, RGB color);
            void set_pixel(int x, int y, int r, int g, int b);
            void fill(RGB color);
            void fill(int r, int g, int b);
            void to_grayscale();
            void to_negative();
    };

}

#endif