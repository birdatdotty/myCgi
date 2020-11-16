cmake_minimum_required(VERSION 3.14)

project(myCgi2Threads LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package(Qt5Test)
#find_package(Qt5Core)

add_executable(myCgi2Threads
  main.cpp
)
target_link_libraries(myCgi2Threads pthread fcgi Qt5::Core Qt5::Test)
