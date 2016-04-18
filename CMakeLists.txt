cmake_minimum_required(VERSION 3.5)
project(CppConcurrencyInAction)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES chapter01/hello.cpp chapter02/2.1.cpp chapter02/2.2.cpp chapter02/2.3.cpp chapter02/2.4.cpp chapter02/2.5.cpp)
add_executable(CppConcurrencyInAction ${SOURCE_FILES})