    cmake_minimum_required(VERSION 3.22)
project(LangAnt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(LangAnt main.cpp paint.h paint.cpp)
target_link_libraries(LangAnt
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

