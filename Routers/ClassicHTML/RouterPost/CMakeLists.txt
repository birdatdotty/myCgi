cmake_minimum_required(VERSION 3.14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Qml Quick REQUIRED)

IF(CMAKE_BUILD_TYPE MATCHES "Debug")
  add_definitions( -DDEBUG )
ENDIF()

include_directories(../Router)

add_library(RouterPost STATIC
  RouterPost.cpp
  RouterPost.h)

target_link_libraries(RouterPost fcgi Qt5::Core Qt5::Qml Qt5::Quick)

#install(TARGETS RouterPost DESTINATION lib/myCgi2/plugins/ClassicHTML)
