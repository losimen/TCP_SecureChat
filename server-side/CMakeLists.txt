list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/main.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/listener.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/clientsocket.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/requesthandler.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/requestexecutor.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/requestvalidator.cpp)

list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/listener.h
                          ${CMAKE_CURRENT_LIST_DIR}/clientsocket.h
                          ${CMAKE_CURRENT_LIST_DIR}/requesthandler.h
                          ${CMAKE_CURRENT_LIST_DIR}/requestexecutor.h
                          ${CMAKE_CURRENT_LIST_DIR}/requestvalidator.h)
