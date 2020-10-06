cmake_minimum_required(VERSION 3.14)
# for build with debug:
# cmake -DCMAKE_BUILD_TYPE=Debug .

project(myCgi2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Qml REQUIRED)

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
IF(CMAKE_BUILD_TYPE MATCHES "Debug")
  message("Debug build.")
  add_definitions( -DDEBUG )
ENDIF()

find_library(FCGI_LIBRARY NAMES fcgi)
add_executable(${CMAKE_PROJECT_NAME}
  main.cpp

  root.qml

  utils.h

  RouterListen.cpp
  RouterListen.h

  Router.cpp
  Router.h
  Router_ParseRequest.cpp
#  Router_default.cpp
#  Router_Js.cpp

#  RouterDefault.cpp
#  RouterDefault.h

  RouterJs.cpp
  RouterJs.h

  RouterPost.cpp
  RouterPost.h

  Obj.cpp
  Obj.h
  ObjGlob.cpp

  Page.cpp
  Page.h

  Chunk.cpp
  Chunk.h
)
target_link_libraries(${CMAKE_PROJECT_NAME} fcgi Qt5::Core Qt5::Qml)
