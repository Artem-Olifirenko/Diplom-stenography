cmake_minimum_required(VERSION 3.5)
project(hiddenwave)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})

find_package(Boost REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp mainwindow.cpp headers/main.h headers/Algorithm.h Algorithm.cpp headers/CustomHeader.h CustomHeader.cpp headers/mainwindow.h)
add_executable(hiddenwave ${SOURCE_FILES})
target_compile_features(hiddenwave PRIVATE cxx_std_17)

target_link_libraries(hiddenwave Qt6::Widgets)
target_link_libraries(hiddenwave ${Boost_LIBRARIES})
