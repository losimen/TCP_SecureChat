#pragma once

#include <QtGlobal>
#include <QString>


struct DBModelUser
{
    qint64 id;
    QString username;
    QString password;
    QString createdAt;
};


typedef QVector<DBModelUser> UserList;
