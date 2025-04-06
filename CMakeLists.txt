cmake_minimum_required(VERSION 3.29)
project(linked_list_sprint_project_Olouxii)

set(CMAKE_CXX_STANDARD 20)


include_directories(
        include
        lib/EventLib
)


add_library(EventLib STATIC
        lib/EventLib/EventFunctions.cpp
)


add_executable(linked_list_sprint_project_Olouxii
        src/main.cpp
        src/funcs.cpp
)


target_link_libraries(linked_list_sprint_project_Olouxii EventLib)