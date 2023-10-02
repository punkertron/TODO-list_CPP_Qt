cmake_minimum_required(VERSION 3.25.1)

project(TODO-tests VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql Test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -g3 -fsanitize=address -fsanitize=leak -fsanitize=undefined")

qt_standard_project_setup()

set(SOURCES
    test_main.cpp
    ../srcs/DbTaskController.cpp
)

set(HEADERS
    ../incs/DbTaskController.hpp
    ../incs/FilterParams.hpp
    ../incs/Task.hpp
    ../incs/SortDialog.hpp
)

qt_add_executable(TODO-tests ${SOURCES} ${HEADERS})

target_link_libraries(TODO-tests PRIVATE Qt6::Core Qt6::Widgets Qt6::Sql Qt6::Test)