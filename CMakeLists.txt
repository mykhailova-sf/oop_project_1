cmake_minimum_required(VERSION 3.26)
project(Sph)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(Sph main.cpp 
        Player.cpp
        Player.h
        Artifact.cpp
        Artifact.h
        textureLoader.h
        textureLoader.cpp
)

target_link_libraries(Sph PRIVATE sfml-system sfml-window sfml-graphics glfw GL GLU SOIL)

