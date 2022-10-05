list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/main.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/windowmanager.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/serversocket.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/cacheemulator.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/inputvalidator.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/windows/iwindow.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/windows/login/login.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/windows/signup/signup.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/windows/mainwindow/mainwindow.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/elements/clickable_qlabel.cpp)


list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/windowmanager.h
                          ${CMAKE_CURRENT_LIST_DIR}/serversocket.h
                          ${CMAKE_CURRENT_LIST_DIR}/cacheemulator.h
                          ${CMAKE_CURRENT_LIST_DIR}/inputvalidator.h
                          ${CMAKE_CURRENT_LIST_DIR}/windows/iwindow.h
                          ${CMAKE_CURRENT_LIST_DIR}/windows/login/login.h
                          ${CMAKE_CURRENT_LIST_DIR}/windows/signup/signup.h
                          ${CMAKE_CURRENT_LIST_DIR}/windows/mainwindow/mainwindow.h
                          ${CMAKE_CURRENT_LIST_DIR}/elements/clickable_qlabel.h)


list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/windows/login/login.ui
                          ${CMAKE_CURRENT_LIST_DIR}/windows/signup/signup.ui
                          ${CMAKE_CURRENT_LIST_DIR}/windows/mainwindow/mainwindow.ui)


list(APPEND myApp_INCLUDES ${CMAKE_CURRENT_LIST_DIR}
                           ${CMAKE_CURRENT_LIST_DIR}/elements
                           ${CMAKE_CURRENT_LIST_DIR}/windows
                           ${CMAKE_CURRENT_LIST_DIR}/windows/login
                           ${CMAKE_CURRENT_LIST_DIR}/windows/signup
                           ${CMAKE_CURRENT_LIST_DIR}/windows/mainwindow)
