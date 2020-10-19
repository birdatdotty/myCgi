cmake_minimum_required(VERSION 3.14)

#project(Router LANGUAGES CXX)

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

add_library(Router STATIC
    Chunk.cpp
    Page.cpp
    QMLTree.cpp
    Router.cpp
    Router_ParseRequest.cpp

    Obj.cpp
    ObjGlob.cpp

    Chunk.h
    Page.h
    QMLTree.h
    Router.h
    utils.h

    Obj.h)

target_link_libraries(Router fcgi Qt5::Core Qt5::Qml Qt5::Quick)

#install(TARGETS Router DESTINATION lib/myCgi2/plugins/ClassicHTML)
