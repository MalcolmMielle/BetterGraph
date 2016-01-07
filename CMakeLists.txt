cmake_minimum_required(VERSION 2.6)
project(bettergraph)

add_executable(bettergraph main.cpp)

install(TARGETS bettergraph RUNTIME DESTINATION bin)

add_subdirectory(include)