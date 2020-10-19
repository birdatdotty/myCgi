cmake_minimum_required(VERSION 3.14)
# for build with debug:
# cmake -DCMAKE_BUILD_TYPE=Debug .
#
# prefix:
# cmake -DCMAKE_INSTALL_PREFIX=/usr .

project(myCgi2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Qml Quick REQUIRED)

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
IF(CMAKE_BUILD_TYPE MATCHES "Debug")
  message("Debug build.")
  add_definitions( -DDEBUG )
ENDIF()

set(PROJ_CONF
    "${CMAKE_INSTALL_PREFIX}/etc/${PROJECT_NAME}/root.qml")

configure_file(config.h.in config.h)

#add_library(Obj SHARED
#    Obj.cpp
#    Obj.h
#    ObjGlob.cpp)
#target_link_libraries(Obj fcgi Qt5::Core Qt5::Qml Qt5::Quick)

add_subdirectory (Routers/ClassicHTML)

set(QML_IMPORT_PATH /usr/local/plugins CACHE STRING "" FORCE)

find_library(FCGI_LIBRARY NAMES fcgi)
add_executable(${CMAKE_PROJECT_NAME}
  main.cpp

  root.qml
  myCgi2.service

  utils.h

  Service.cpp
  Service.h

  RouterListen.cpp
  RouterListen.h

  ChangeLog
  INSTALL
  README.md
)
target_link_libraries(${CMAKE_PROJECT_NAME} Router #[[Obj ]] fcgi Qt5::Core Qt5::Qml Qt5::Quick)

install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION bin)

#install(TARGETS Obj                   DESTINATION lib)
#install(FILES   Obj.h                 DESTINATION include)

install(FILES   root.qml              DESTINATION etc/${CMAKE_PROJECT_NAME})
install(FILES   myCgi2.service        DESTINATION lib/systemd/system)
