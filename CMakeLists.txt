cmake_minimum_required(VERSION 3.18)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C++_STANDARD 17)

project(Raytracer CXX)

add_subdirectory(WindowManager)
link_directories(./dependencies/math3D)

include_directories(
  ./
  ./dependencies/
  ./WindowManager/window
)

add_executable(Raytracer main.cpp)

target_link_libraries(Raytracer 
  window
  math3D
)

