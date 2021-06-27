project(logger_test)

cmake_minimum_required(VERSION 2.6)

add_compile_options(-std=c++11)

find_package(Threads REQUIRED)

add_executable(loggerTest ./main.cpp)
target_link_libraries(loggerTest Threads::Threads)