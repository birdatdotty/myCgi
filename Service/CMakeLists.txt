cmake_minimum_required(VERSION 3.11)

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

add_library(Service STATIC
    Service.cpp
    RouterListen.cpp
    FCGIRequest.cpp
    ObjGlob.cpp
    Chunk.cpp
    Router.cpp
    Router_ParseRequest.cpp
    QMLTree.cpp
    Request.cpp
    DefaultPage.cpp
    Script.cpp
    Page.cpp

    RouterCSS.cpp
    RouterJS.cpp


    RouterListen.h
    Service.h
    FCGIRequest.h
    ObjGlob.h
    Chunk.h
    Router.h
    QMLTree.h
    Request.h
    DefaultPage.h
    Script.h
    Page.h

    RouterCSS.h
    RouterJS.h)

target_link_libraries(Service fcgi Qt5::Core Qt5::Qml Qt5::Quick Qt5::Test)

#install(TARGETS ClassicHTML DESTINATION lib/${CMAKE_PROJECT_NAME}/plugins/ClassicHTML)
#install(FILES qmldir DESTINATION lib/${CMAKE_PROJECT_NAME}/plugins/ClassicHTML)
