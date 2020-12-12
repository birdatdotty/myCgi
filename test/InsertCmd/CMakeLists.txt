cmake_minimum_required(VERSION 3.14)

project(InsertCmd LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

IF(CMAKE_BUILD_TYPE MATCHES "Debug")
  message("\n\n--------------------")
  message("Debug build.")
  message("--------------------")
  add_definitions( -DDEBUG )
ENDIF()


find_package(Qt5Core)

add_executable(${CMAKE_PROJECT_NAME}
  main.cpp

  InsertCmd.cpp
  InsertCmd.h
)
target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Core)
