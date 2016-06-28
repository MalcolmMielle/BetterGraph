#for debug : cmake -DCMAKE_BUILD_TYPE=Debug /path/to/source

cmake_minimum_required(VERSION 2.6)
project(bettergraph)

SET(CMAKE_CXX_FLAGS "-Wall")
# Version for all the file in debug have TIMED defined in debug mode
SET(CMAKE_CXX_FLAGS_DEBUG  "-DDEBUG -g")

include_directories(include)

add_executable(bettergraph main.cpp)
add_executable(simplegraph simplegraph.cpp)
add_executable(directedpseudograph directedpseudo.cpp)

install(TARGETS bettergraph RUNTIME DESTINATION bin)
install(TARGETS simplegraph RUNTIME DESTINATION bin)
install(TARGETS directedpseudograph RUNTIME DESTINATION bin)

add_subdirectory(include)


# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)


## Installing the files

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
INSTALL(FILES ${files} DESTINATION include/bettergraph)
INSTALL(FILES bettergraph-config.cmake DESTINATION lib/bettergraph)



## If rpm wanted

SET(CPACK_GENERATOR "RPM")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Malcolm Mielle") #required
 
INCLUDE(CPack)
