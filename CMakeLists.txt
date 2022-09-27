cmake_minimum_required(VERSION 3.14)

project(SecureChat LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(BUILD_SERVER FALSE)
set(BUILD_CLIENT FALSE)

if(BUILD_CLIENT)
    include(client-side/CMakeLists.txt)
    add_subdirectory(client-side)
    add_executable(SecureChat ${myApp_SOURCES})
endif()

if(BUILD_SERVER)
    include(server-side/CMakeLists.txt)
    add_subdirectory(server-side)
    add_executable(SecureChat ${myApp_SOURCES})
endif()

target_link_libraries(SecureChat Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS SecureChat
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
