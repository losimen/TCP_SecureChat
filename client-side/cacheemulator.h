#pragma once

#include <QtGlobal>
#include <QString>

#include "clientmodelchat.h"
#include "clientmodelmessage.h"


class CacheEmulator
{
public:
    static CacheEmulator &getInstance();

    const QString getAccessToken();
    void setAccessToken(const QString &accessToken);
    void insertChat(const ClientModelChat &chat);
    void insertMessage(const ClientModelMessage &message);

private:
    CacheEmulator();

    QString accessToken;

    ClientChatList chatList;
    ClientMessageList messageList;
};
