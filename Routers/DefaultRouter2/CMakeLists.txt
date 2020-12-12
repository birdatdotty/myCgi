cmake_minimum_required(VERSION 3.11)

set(MODULE "DefaultRouter")
configure_file(qmldir.in qmldir)

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

include_directories(../../Service)

add_library(DefaultRouter SHARED
    DefaultRouter.cpp
    DefaultRouter.h

    RouterCSS.cpp
    RouterHTML.cpp
    RouterJS.cpp
    RouterPost.cpp
    RouterChunk.cpp

    RouterCSS.h
    RouterHTML.h
    RouterJS.h
    RouterPost.h
    RouterChunk.h)


target_link_libraries(DefaultRouter
    fcgi
#    /usr/local/lib/myCgi2/libService.a

    Qt5::Core
    Qt5::Qml
    Qt5::Quick)

install(TARGETS ${MODULE} DESTINATION lib/${CMAKE_PROJECT_NAME}/plugins/${MODULE})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qmldir DESTINATION lib/${CMAKE_PROJECT_NAME}/plugins/${MODULE})
