list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/types/ServerTypes.h
                          ${CMAKE_CURRENT_LIST_DIR}/types/ClientTypes.h)

list(APPEND myApp_INCLUDES ${CMAKE_CURRENT_LIST_DIR}
                           ${CMAKE_CURRENT_LIST_DIR}/types)
