cmake_minimum_required(VERSION 3.14)
project("SO2_project")

set(CMAKE_CXX_STANDARD 17)



set(SOURCES
        main.cpp
        src/Flower.h
        src/Flower.cpp)

add_executable(main_app ${SOURCES})


# Adding sfml
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(main_app ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

