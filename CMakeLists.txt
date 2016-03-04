cmake_minimum_required(VERSION 2.6)
project(bettergraph)

SET(CMAKE_CXX_FLAGS "-Wall")
# Version for all the file in debug have TIMED defined in debug mode
SET(CMAKE_CXX_FLAGS_DEBUG  "-DDEBUG -g")

include_directories(include)

add_executable(bettergraph main.cpp)
add_executable(simplegraph simplegraph.cpp)

install(TARGETS bettergraph RUNTIME DESTINATION bin)
install(TARGETS simplegraph RUNTIME DESTINATION bin)

add_subdirectory(include)