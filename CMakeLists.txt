cmake_minimum_required(VERSION 3.25.1)

project(TODO_App VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS  "-std=c++17 -g3 -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

#bad practice?
file(GLOB ALL_SOURCE_FILES srcs/*.cpp srcs/*.hpp)

qt_add_executable(TODO_App ${ALL_SOURCE_FILES})

add_custom_target(
    clangformat
    ALL
    COMMAND clang-format
    -i
    ${ALL_SOURCE_FILES}
)

target_link_libraries(TODO_App PRIVATE Qt6::Core Qt6::Widgets)