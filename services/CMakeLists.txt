list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/security/security.h
                          ${CMAKE_CURRENT_LIST_DIR}/security/base64.h
                          ${CMAKE_CURRENT_LIST_DIR}/types/servertypes.h
                          ${CMAKE_CURRENT_LIST_DIR}/types/clienttypes.h
                          ${CMAKE_CURRENT_LIST_DIR}/types/itype.h
                          ${CMAKE_CURRENT_LIST_DIR}/errors/servererrors.h
                          ${CMAKE_CURRENT_LIST_DIR}/errors/dberrors.h
                          ${CMAKE_CURRENT_LIST_DIR}/protocol/requestmethods.h
                          ${CMAKE_CURRENT_LIST_DIR}/protocol/statuscodes.h
                          ${CMAKE_CURRENT_LIST_DIR}/models/dbmodelchat.h
                          ${CMAKE_CURRENT_LIST_DIR}/models/dbmodelmessage.h
                          ${CMAKE_CURRENT_LIST_DIR}/models/dbmodeluser.h)


list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/security/security.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/security/base64.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/types/servertypes.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/types/clienttypes.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/types/itype.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/protocol/requestmethods.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/protocol/statuscodes.cpp)


list(APPEND myApp_INCLUDES ${CMAKE_CURRENT_LIST_DIR}
                           ${CMAKE_CURRENT_LIST_DIR}/security
                           ${CMAKE_CURRENT_LIST_DIR}/types
                           ${CMAKE_CURRENT_LIST_DIR}/errors
                           ${CMAKE_CURRENT_LIST_DIR}/protocol
                           ${CMAKE_CURRENT_LIST_DIR}/models)
