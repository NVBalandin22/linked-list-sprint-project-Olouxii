cmake_minimum_required(VERSION 3.29)
project(linked_list_sprint_project_Olouxii)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(linked_list_sprint_project_Olouxii
        src/EventFunctions.cpp
        src/main.cpp
        src/funcs.cpp
        include/EventFunctions.h
        include/Event.h
        include/funcs.h)