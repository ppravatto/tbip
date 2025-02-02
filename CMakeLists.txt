cmake_minimum_required(VERSION 3.12.0)

project(tbip VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "$<$<CONFIG:DEBUG>:-O0;-g>"
)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
  set(LIBS ${LIBS} OpenMP::OpenMP_CXX)
endif()

add_library(tbip SHARED src/tbip.cpp src/colormaps.cpp)
set_target_properties(tbip PROPERTIES PUBLIC_HEADER "include/tbip.h;include/tbip_exceptions.h;include/tbip_colormaps.h")
set_target_properties(tbip PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(tbip PRIVATE include)
target_include_directories(tbip PRIVATE src)
target_link_libraries(tbip ${LIBS})

option(COMPILE_EXAMPLES "Set whether the examples are compiled" OFF)
if(COMPILE_EXAMPLES)
    set(EXAMPLES_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/bin" CACHE PATH "Set example installation path")
    
    add_executable(simple examples/simple.cpp)
    target_include_directories(simple PRIVATE include)
    target_link_libraries(simple PRIVATE tbip)

    add_executable(function examples/function.cpp)
    target_include_directories(function PRIVATE include)
    target_link_libraries(function PRIVATE tbip)

    add_executable(colorbars examples/colorbars.cpp)
    target_include_directories(colorbars PRIVATE include)
    target_link_libraries(colorbars PRIVATE tbip)

    add_executable(mandelbrot examples/mandelbrot.cpp)
    target_include_directories(mandelbrot PRIVATE include)
    target_link_libraries(mandelbrot PRIVATE tbip)

    install(
        TARGETS simple function colorbars mandelbrot
        RUNTIME DESTINATION "${EXAMPLES_INSTALL_PATH}"
        )
endif()

install(
    TARGETS tbip
    LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
    )





