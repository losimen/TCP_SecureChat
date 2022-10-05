#pragma once

#include <QtGlobal>
#include <QString>
#include <QVector>


struct DBModelChat
{
    qint64 id;
    qint64 creatorId;
    QString chatName;
    QString createdAt;
};


typedef QVector<DBModelChat> ChatList;
