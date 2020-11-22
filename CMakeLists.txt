cmake_minimum_required(VERSION 3.11)
# for build with debug:
# cmake -DCMAKE_BUILD_TYPE=Debug .
#
# prefix:
# cmake -DCMAKE_INSTALL_PREFIX=/usr .

project(myCgi2
    VERSION 0.5.1
    DESCRIPTION "myCgi2lib description"
    LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Qml Quick REQUIRED)
find_package(Qt5Test)


message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
IF(CMAKE_BUILD_TYPE MATCHES "Debug")
  message("Debug build.")
  add_definitions( -DDEBUG )
ENDIF()

set(PROJ_CONF
    "${CMAKE_INSTALL_PREFIX}/etc/${PROJECT_NAME}/root.qml")

configure_file(config.h.in config.h)
configure_file(root.qml.in root.qml)
configure_file(myCgi2.pc.in ${CMAKE_PROJECT_NAME}.pc @ONLY)
configure_file(myCgi2.service.in ${CMAKE_PROJECT_NAME}.service)

#add_library(Obj SHARED
#    Obj.cpp
#    Obj.h
#    ObjGlob.cpp)
#target_link_libraries(Obj fcgi Qt5::Core Qt5::Qml Qt5::Quick)

add_subdirectory(Service)
#include_directories(Service)

set(QML_IMPORT_PATH ${CMAKE_INSTALL_PREFIX}/plugins CACHE STRING "" FORCE)

find_library(FCGI_LIBRARY NAMES fcgi)

#include_directories(Routers/ClassicHTML/Router)

add_executable(${CMAKE_PROJECT_NAME}
  main.cpp

#  Service.cpp
#  Service.h

#  RouterListen.cpp
#  RouterListen.h

# other files (need for qtcreator)
  config.h.in
  myCgi2.pc.in
  myCgi2.service.in

  root.qml
  root2.qml
  root3.qml
  ChangeLog
  INSTALL
  README.md
)

target_link_libraries(${CMAKE_PROJECT_NAME} Service fcgi Qt5::Core Qt5::Qml Qt5::Quick)


install(TARGETS ${CMAKE_PROJECT_NAME}
    DESTINATION bin)

install(FILES   ${CMAKE_BINARY_DIR}/root.qml
    DESTINATION etc/${CMAKE_PROJECT_NAME})

install(FILES   ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.service
    DESTINATION lib/systemd/system)

install(FILES ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.pc
    DESTINATION lib/pkgconfig)

#chunks  css  html  js  scripts
install(DIRECTORY web/
    DESTINATION var/${CMAKE_PROJECT_NAME})
