cmake_minimum_required(VERSION 3.7)
project(wopwop)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        src/button.c
        src/button.h
        src/main.c
        src/texture.c
        src/texture.h)

include_directories(/usr/local/include/)
link_directories(/usr/local/lib)
add_executable(wopwop ${SOURCE_FILES})
target_link_libraries(wopwop SDL2 SDL2_image SDL2_ttf)
