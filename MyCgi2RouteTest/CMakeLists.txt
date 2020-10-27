cmake_minimum_required(VERSION 3.14)
# for build with debug:
# cmake -DCMAKE_BUILD_TYPE=Debug .
project(MyCgi2RouteTest)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
find_package(Qt5 COMPONENTS Core Qml Quick REQUIRED)

configure_file(qmldir.in qmldir)

pkg_check_modules(MYCGI REQUIRED myCgi2)
#pkg_search_module(MYCGI REQUIRED myCgi)

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
IF(CMAKE_BUILD_TYPE MATCHES "Debug")
  message("Debug build.")
  add_definitions( -DDEBUG )
ENDIF()

add_library(${CMAKE_PROJECT_NAME} SHARED
  mycgi2routetest_plugin.cpp
  mycgi2routetest.cpp
)
target_link_libraries(${CMAKE_PROJECT_NAME} fcgi Qt5::Core Qt5::Qml Qt5::Quick)

install(TARGETS ${CMAKE_PROJECT_NAME}
    DESTINATION "${MYCGI_LIBRARY_DIRS}/plugins/${CMAKE_PROJECT_NAME}")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qmldir
    DESTINATION "${MYCGI_LIBRARY_DIRS}/plugins/${CMAKE_PROJECT_NAME}")
