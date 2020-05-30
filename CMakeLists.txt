cmake_minimum_required(VERSION 3.12)
project(interpolering LANGUAGES CXX)

add_subdirectory(libs)



include_directories(include/)

add_executable(interpolering
  src/main.cpp
  src/data.cpp include/data.h
  src/interpolation.cpp include/interpolation.h
  include/point.h include/point_collection.h
)

target_link_libraries(interpolering PUBLIC ImGui-SFML::ImGui-SFML)
