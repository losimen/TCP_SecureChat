#pragma once

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
    static ClientTypes::GetMessageList getMessageList(SQLDatabase &db, const ServerTypes::GetMessageList &getMessageList_server);
    static ClientTypes::GetChatList getChatList(SQLDatabase &db, const ServerTypes::GetChatList &getChatList_server);
    static ClientTypes::GetUpdates getUpdates(SQLDatabase &db, const ServerTypes::GetUpdates &getUpdates_server);
    static ClientTypes::GetPubKey getPubKey(SQLDatabase &db, const ServerTypes::GetPubKey &getPubKey_server);

};

