list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/main.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/listener.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/clientsocket.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/request/requesthandler.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/request/requestexecutor.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/request/requestvalidator.cpp)

list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/listener.h
                          ${CMAKE_CURRENT_LIST_DIR}/clientsocket.h
                          ${CMAKE_CURRENT_LIST_DIR}/request/requesthandler.h
                          ${CMAKE_CURRENT_LIST_DIR}/request/requestexecutor.h
                          ${CMAKE_CURRENT_LIST_DIR}/request/requestvalidator.h)

list(APPEND myApp_INCLUDES ${CMAKE_CURRENT_LIST_DIR}
                           ${CMAKE_CURRENT_LIST_DIR}/request)
