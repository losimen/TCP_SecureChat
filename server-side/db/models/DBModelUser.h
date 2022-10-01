#ifndef DBMODELUSER_H
#define DBMODELUSER_H

#include <QtGlobal>
#include <QString>


struct DBModelUser
{
    qint64 id;
    QString username;
    QString password;
    QString createdAt;
};

#endif // DBMODELUSER_H
