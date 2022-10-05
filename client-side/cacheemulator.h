#pragma once

#include <QtGlobal>
#include <QString>

#include "dbmodelchat.h"


class CacheEmulator
{
public:
    static CacheEmulator &getInstance();

    const QString getAccessToken();
    void setAccessToken(const QString &accessToken);

    void insertChat(const DBModelChat &chat);

private:
    CacheEmulator();

    QString accessToken;
    ChatList chatList;

};
