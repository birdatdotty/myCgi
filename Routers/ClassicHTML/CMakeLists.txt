cmake_minimum_required(VERSION 3.14)

#project(Router LANGUAGES CXX)
project(Router
    VERSION 1.0.1
    DESCRIPTION "myCgi2Router description"
    LANGUAGES CXX)


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

add_subdirectory (Router)
add_subdirectory (RouterJS)
add_subdirectory (RouterCSS)
add_subdirectory (RouterPost)

add_library(ClassicHTML SHARED
    ClassicHTMLRouter.cpp
    ClassicHTMLRouter.h)

target_link_libraries(ClassicHTML Router RouterJS RouterCSS RouterPost fcgi Qt5::Core Qt5::Qml Qt5::Quick)

install(TARGETS ClassicHTML DESTINATION lib/myCgi2/plugins/ClassicHTML)
install(FILES qmldir DESTINATION lib/myCgi2/plugins/ClassicHTML)
