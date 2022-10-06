#pragma once

#include <QtGlobal>
#include <QString>

#include "dbmodelchat.h"
#include "dbmodelmessage.h"
#include "dbmodeluser.h"


class CacheEmulator
{
public:
    static CacheEmulator &getInstance();

    const QString getAccessToken();
    const QString getCurrentUsername();

    void setAccessToken(const QString &accessToken);
    void setCurrentUsername(const QString &username);

    void insertChat(const DBModelChat &chat);
    void insertMessage(const DBModelMessage &message);

    static const QString getChatFullName(const QString &chatName, const qint64 chatId);
    static const qint64 getChatIdFromFullName(const QString &buffer);

private:
    CacheEmulator();

    QString accessToken;

    DBModelUser currentUser;

    DBChatList chatList;
    DBMessageList messageList;
};
