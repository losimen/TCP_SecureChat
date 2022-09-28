list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/types/servertypes.h
                          ${CMAKE_CURRENT_LIST_DIR}/types/clienttypes.h
                          ${CMAKE_CURRENT_LIST_DIR}/errors/servererrors.h
                          ${CMAKE_CURRENT_LIST_DIR}/requestmethods.h)

list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/types/servertypes.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/requestmethods.cpp)

list(APPEND myApp_INCLUDES ${CMAKE_CURRENT_LIST_DIR}
                           ${CMAKE_CURRENT_LIST_DIR}/types
                           ${CMAKE_CURRENT_LIST_DIR}/errors)
