#pragma once

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
