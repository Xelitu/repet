cmake_minimum_required(VERSION 3.10)

project(repet
    VERSION 0.1
    DESCRIPTION "A simple drawing application using Qt"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(SOURCES
    src/Repet.cpp
    src/MainWindow.cpp
    src/DrawingWidget.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} )

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)