list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/main.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/windowmanager.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/inputvalidator.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/windows/login/login.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/windows/signup/signup.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/elements/clickable_qlabel.cpp)


list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/windowmanager.h
                          ${CMAKE_CURRENT_LIST_DIR}/inputvalidator.h
                          ${CMAKE_CURRENT_LIST_DIR}/windows/login/login.h
                          ${CMAKE_CURRENT_LIST_DIR}/windows/signup/signup.h
                          ${CMAKE_CURRENT_LIST_DIR}/elements/clickable_qlabel.h)


list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/windows/login/login.ui
                          ${CMAKE_CURRENT_LIST_DIR}/windows/signup/signup.ui)


list(APPEND myApp_INCLUDES ${CMAKE_CURRENT_LIST_DIR}
                           ${CMAKE_CURRENT_LIST_DIR}/elements
                           ${CMAKE_CURRENT_LIST_DIR}/windows
                           ${CMAKE_CURRENT_LIST_DIR}/windows/login
                           ${CMAKE_CURRENT_LIST_DIR}/windows/signup)
