#ifndef REQUESTEXECUTOR_H
#define REQUESTEXECUTOR_H

#include <QString>

#include "servertypes.h"
#include "clienttypes.h"
#include "sqldatabase.h"


class RequestExecutor
{
public:
    RequestExecutor();

    static ClientTypes::Error error(const StatusCodes &statusCode, const QString &what);

    static ClientTypes::LogIn logIn(SQLDatabase &db, const ServerTypes::LogIn &logIn_server);
    static ClientTypes::SignUp signUp(SQLDatabase &db, const ServerTypes::SignUp &signUp_server);
    static ClientTypes::CreateChat createChat(SQLDatabase &db, const ServerTypes::CreateChat &createChat_server);
    static ClientTypes::AddMember addMember(SQLDatabase &db, const ServerTypes::AddMember &addMember_server);
    static ClientTypes::SendMessage sendMessage(SQLDatabase &db, const ServerTypes::SendMessage &sendMessage_server);
};

#endif // REQUESTEXECUTOR_H
