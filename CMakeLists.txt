cmake_minimum_required(VERSION 3.14)

project(SecureChat LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(OPENSSL_INCLUDE_DIR /opt/homebrew/opt/openssl@3/include)
set(OPENSSL_LIBRARIES /opt/homebrew/opt/openssl@3/lib)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Quick)


set(BUILD_SERVER FALSE)
set(BUILD_CLIENT FALSE)

include(services/CMakeLists.txt)
add_subdirectory(services)

if(BUILD_CLIENT)
    include(client-side/CMakeLists.txt)
    add_subdirectory(client-side)
    QT6_WRAP_UI(UI_HEADERS ${UIS})
    add_executable(SecureChat ${myApp_SOURCES})
endif()

if(BUILD_SERVER)
    include(server-side/CMakeLists.txt)
    add_subdirectory(server-side)
    add_executable(SecureChat ${myApp_SOURCES})
endif()

include_directories(${myApp_INCLUDES})

target_link_libraries(SecureChat Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(SecureChat Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(SecureChat Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(SecureChat Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(SecureChat Qt${QT_VERSION_MAJOR}::Quick)
target_link_libraries(SecureChat OpenSSL::SSL OpenSSL::Crypto)

install(TARGETS SecureChat LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
