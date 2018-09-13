# https://cmake.org/pipermail/cmake/2011-March/043534.html

project(visualizador)
cmake_minimum_required(VERSION 2.8)

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

find_package(PkgConfig REQUIRED)
# Find SDL2

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_gfx REQUIRED SDL2_gfx)

# Add global definitions
add_definitions("-Wall -O2")
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_gfx_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")
set(SIMD "-mavx2 -ffast-math -ftree-vectorize")
set(OMP "-fopenmp")

add_executable(billiards_seq main.cpp visualizador.cpp ball.cpp geometry.cpp)
add_executable(billiards_omp main.cpp visualizador.cpp ball.cpp geometry.cpp)
add_executable(billiards_simd main.cpp visualizador.cpp ball.cpp geometry.cpp)
add_executable(billiards_seq_nogui main_nogui.cpp visualizador_nogui.cpp ball.cpp geometry.cpp)
add_executable(billiards_omp_nogui main_nogui.cpp visualizador_nogui.cpp ball.cpp geometry.cpp)
add_executable(billiards_simd_nogui main_nogui.cpp visualizador_nogui.cpp ball.cpp geometry.cpp)

target_link_libraries(billiards_seq ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES})
target_link_libraries(billiards_omp ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES})
target_link_libraries(billiards_simd ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES})
target_link_libraries(billiards_seq_nogui ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES})
target_link_libraries(billiards_omp_nogui ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES})
target_link_libraries(billiards_simd_nogui ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES})

SET_TARGET_PROPERTIES(billiards_omp PROPERTIES COMPILE_FLAGS ${OMP} LINK_FLAGS ${OMP})
SET_TARGET_PROPERTIES(billiards_simd PROPERTIES COMPILE_FLAGS ${SIMD} LINK_FLAGS ${SIMD})
SET_TARGET_PROPERTIES(billiards_omp_nogui PROPERTIES COMPILE_FLAGS ${OMP} LINK_FLAGS ${OMP})
SET_TARGET_PROPERTIES(billiards_simd_nogui PROPERTIES COMPILE_FLAGS ${SIMD} LINK_FLAGS ${SIMD})
