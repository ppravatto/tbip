#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include "tbip.h"


namespace tbip{

    //Define the RGB class to store and manipulate RGB values
    //------------------------------------------------------------------------------

    RGB::RGB() : r(0), g(0), b(0) {};

    RGB::RGB(int r_, int g_, int b_) : r(r_), g(g_), b(b_) {};

    RGB RGB::get_graylevel(){
        int avg = int((r+g+b)/3.);
        RGB grayscale(avg, avg, avg);
        return grayscale;
    }



    //Define the Image class
    //------------------------------------------------------------------------------

    void Image::copy(const Image& source){
        if(source.init == false) throw(_exceptions_::InitError());
        if(init == true) delete[] data;
        width = source.width; height = source.height; max = source.max; init=true;
        data = new RGB [width*height];
        for(int i=0; i<width*height; i++) data[i] = source.data[i];
    }

    void Image::check_init(){
        if(init == false) throw(_exceptions_::InitError());
    }

    void Image::check_color(RGB color){
        if(color.r < 0 || color.r >= max || color.g < 0 || color.g >= max ||color.b < 0 || color.b >= max)
            throw(_exceptions_::ColorMaxError());
    }

    void Image::check_pixel(int x, int y){
        if(x < 0 || x >= width || y < 0 || y >= height)
            throw(_exceptions_::PositionError());
    }

    Image::Image() : init(false), width(0), height(0), max(0) {};

    Image::Image(int width_, int height_, int max_) : init(true), width(width_), height(height_), max(max_) {
        data = new RGB [width*height];
    }

    Image::Image(int width_, int height_, int max_, RGB* data_) : Image(width_, height_, max_) {
        for(int i=0; i<width*height; i++){
            check_color(data_[i]);
            data[i] = data_[i];
        }
    }

    Image::Image(const Image& source){
        copy(source);
    }

    Image::~Image(){
        if(init == true) delete[] data;
    }

    Image& Image::operator= (const Image& source){
        copy(source);
        return *this;
    };

    void Image::save(std::string filename){
        std::ofstream file(filename);
        file << "P3" << std::endl;
        file << width << " " << height << std::endl;
        file << max << std::endl;
        for(int x=0; x<height; x++){
            for(int y=0; y<width; y++){
                int idx = x + width*y;
                if(y != 0) file << '\t';
                file << data[idx].r << " " << data[idx].g << " " << data[idx].b;
            }
            file << std::endl;
        }
        file.close();
    }

    void Image::set_pixel(int x, int y, RGB color){
        check_init();
        check_pixel(x, y);
        check_color(color);
        int idx = x + width*y;
        data[idx] = color;
    }

    void Image::set_pixel(int x, int y, int r, int g, int b){
        check_init();
        RGB color(r, g, b);
        set_pixel(x, y, color);
    }

    void Image::fill(RGB color){
        check_init();
        check_color(color);
        for(int i=0; i<width*height; i++) data[i] = color;
    }

    void Image::fill(int r, int g, int b){
        RGB color(r, g, b);
        fill(color);
    }

    void Image::to_grayscale(){
        check_init();
        for(int i=0; i<width*height; i++) data[i] = data[i].get_graylevel();
    }

    void Image::to_negative(){
        check_init();
        for(int i=0; i<width*height; i++){
            int neg_r = max - data[i].r - 1;
            int neg_g = max - data[i].g - 1;
            int neg_b = max - data[i].b - 1;
            RGB color(neg_r, neg_g, neg_b);
            data[i] = color;
        }
    }

}