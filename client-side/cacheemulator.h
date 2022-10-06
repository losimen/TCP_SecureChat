#pragma once

#include <QtGlobal>
#include <QString>

#include "clientmodelchat.h"
#include "clientmodelmessage.h"
#include "clientmodeluser.h"


class CacheEmulator
{
public:
    static CacheEmulator &getInstance();

    const QString getAccessToken();
    const QString getCurrentUsername();

    void setAccessToken(const QString &accessToken);
    void setCurrentUsername(const QString &username);

    void insertChat(const ClientModelChat &chat);
    void insertMessage(const ClientModelMessage &message);


private:
    CacheEmulator();

    QString accessToken;

    ClientModelUser currentUser;

    ClientChatList chatList;
    ClientMessageList messageList;
};
