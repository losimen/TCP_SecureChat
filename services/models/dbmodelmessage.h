#pragma once

#include <QtGlobal>
#include <QString>


struct DBModelMessage
{
    qint64 id;
    qint64 senderId;
    QString sendeUsername;
    qint64 chatId;

    QString createdAt;
    QString msgText;
};


typedef QVector<DBModelMessage> DBMessageList;
