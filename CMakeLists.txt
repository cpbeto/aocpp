cmake_minimum_required(VERSION 3.17)
project(AOC-Demo)

set(CMAKE_CXX_STANDARD 20)

#if (MSVC)
#    add_compile_options(/W4)
#else()
#    add_compile_options(-Wall -Wextra -pedantic)
#endif()

add_executable(AOC-Demo main.cpp graphics.cpp graphics.h map/Map.cpp map/Map.h map/MapLoader.cpp map/MapLoader.h grh/GrhLoader.cpp grh/GrhLoader.h grh/GrhData.cpp grh/GrhData.h texture/TextureLoader.cpp texture/TextureLoader.h MapRenderer.cpp MapRenderer.h)

target_link_libraries(AOC-Demo SDL2)