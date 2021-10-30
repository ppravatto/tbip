#ifndef TBIP_EXCEPTIONS_H
#define TBIP_EXCEPTIONS_H

#include <exception>

namespace tbip{

    namespace _exceptions_{

        class InitError: public std::exception {
            virtual const char* what() const throw(){
                return "operation performed on uninitilized object";
            }
        };

        class ColorMaxError: public std::exception {
            virtual const char* what() const throw(){
                return "invalid color";
            }
        };

        class PositionError: public std::exception {
            virtual const char* what() const throw(){
                return "invalid pixel coordinates";
            }
        };

        class PpmMaxValError: public std::exception {
            virtual const char* what() const throw(){
                return "invalid maximum color value for .ppm file";
            }
        };

        class InitValError: public std::exception {
            virtual const char* what() const throw(){
                return "invalid initialization parameter";
            }
        };

        class ValueError: public std::exception {
            virtual const char* what() const throw(){
                return "invalid value";
            }
        };

    }

}

#endif