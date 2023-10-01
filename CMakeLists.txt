cmake_minimum_required(VERSION 3.25.1)

project(TODO-list VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(DEBUG_MODE "Enable debug build" OFF)

if(DEBUG_MODE)
    set(CMAKE_CXX_FLAGS  "-std=c++17 -Wall -Wextra -g3 -fsanitize=address -fsanitize=leak -fsanitize=undefined")
else()
    set(CMAKE_CXX_FLAGS  "-std=c++17 -Wall -Wextra -O2")
endif()

qt_standard_project_setup()

set(SOURCES
    srcs/AddTaskDialog.cpp
    srcs/DbTaskController.cpp 
    srcs/main.cpp
    srcs/TaskWidget.cpp
    srcs/ChangeParametersDialog.cpp
    srcs/FilterDialog.cpp
    srcs/MainWindow.cpp
)

SET(HEADERS
    incs/AddTaskDialog.hpp
    incs/DbTaskController.hpp
    incs/FilterParams.hpp
    incs/Task.hpp
    incs/ChangeParametersDialog.hpp
    incs/FilterDialog.hpp
    incs/MainWindow.hpp
    incs/TaskWidgwet.hpp
)

qt_add_executable(TODO-list ${SOURCES} ${HEADERS})

# format code. runs first
add_custom_target(
    clang-format
    ALL
    COMMAND clang-format -i ${SOURCES} ${HEADERS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VERBATIM
)

target_link_libraries(TODO-list PRIVATE Qt6::Core Qt6::Widgets Qt6::Sql)

add_dependencies(TODO-list clang-format)