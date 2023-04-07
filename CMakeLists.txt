cmake_minimum_required(VERSION 3.2)

project(
  canvas-manager
  VERSION 1.0.0
  LANGUAGES CXX)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(canvas-manager-binary app/main.cpp ${SOURCE_FILES})
  
target_include_directories(canvas-manager-binary PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_compile_features(canvas-manager-binary PRIVATE cxx_std_17)