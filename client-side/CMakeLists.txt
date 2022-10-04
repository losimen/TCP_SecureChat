list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/main.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/windowmanager.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/windows/login.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/windows/signup.cpp)


list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/windowmanager.h
                          ${CMAKE_CURRENT_LIST_DIR}/windows/login.h
                          ${CMAKE_CURRENT_LIST_DIR}/windows/signup.h)


list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/windows/login.ui
                          ${CMAKE_CURRENT_LIST_DIR}/windows/signup.ui)


list(APPEND myApp_INCLUDES ${CMAKE_CURRENT_LIST_DIR}
                           ${CMAKE_CURRENT_LIST_DIR}/windows)
