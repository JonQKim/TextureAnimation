cmake_minimum_required(VERSION 3.22.1)

project("Native")

add_library(${CMAKE_PROJECT_NAME} SHARED
    TextureAnimation.cpp
    Matrix.cpp
    Texture.cpp)

set(LIB_DEPENDENCIES "")
list(APPEND LIB_DEPENDENCIES "-lEGL")
list(APPEND LIB_DEPENDENCIES "-lGLESv3")

target_link_libraries(${CMAKE_PROJECT_NAME}
    android ${LIB_DEPENDENCIES}
    log)
