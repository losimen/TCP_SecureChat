#pragma once

#include "dbmodelchat.h"


struct ClientModelChat: public DBModelChat
{
    qint64 clientId;

    const QString getFullName();
    static const qint64 getChatIdFromFullName(const QString &buffer);
};


typedef QVector<ClientModelChat> ClientChatList;
