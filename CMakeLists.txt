cmake_minimum_required(VERSION 3.28)
project(QBCalculator)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        QBCalculator
        src/APIs/ASCII_ART_API.hpp
        src/APIs/COLOR_CODING_API.hpp
        src/Headers/QB_BackEnd.hpp
        src/Headers/paint.hpp
        src/Headers/QB_Banners.hpp
        src/Headers/QB_FrontEnd.hpp
        src/main.cpp
)