#ifndef DBMODELMESSAGE_H
#define DBMODELMESSAGE_H

#include <QtGlobal>
#include <QString>


struct DBModelMessage
{
    qint64 id;
    qint64 senderId;
    qint64 chatId;

    QString createdAt;
    QString msgText;
};


typedef QVector<DBModelMessage> MessageList;

#endif // DBMODELMESSAGE_H
