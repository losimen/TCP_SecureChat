#ifndef DBMODELCHAT_H
#define DBMODELCHAT_H

#include <QtGlobal>
#include <QString>


struct DBModelChat
{
    qint64 id;
    qint64 creatorId;
    QString chatName;
    QString createdAt;
};


typedef QVector<DBModelChat> ChatList;

#endif // DBMODELCHAT_H
