#ifndef CLIENTTYPES_H
#define CLIENTTYPES_H

#include <QtGlobal>
#include <QString>
#include <QJsonObject>

#include "statuscodes.h"


namespace ClientTypes
{

struct LogIn
{
private:
    StatusCodes statusCode;
    QString accessToken;

public:
    void parseData(const StatusCodes &statusCode, const QString &accessToken);
    QByteArray serializeData() const;

};


struct SignUp
{
private:
    StatusCodes statusCode;
    QString accessToken;

public:
    void parseData(const StatusCodes &statusCode, const QString &accessToken);
    QByteArray serializeData() const;

};
}

#endif // CLIENTTYPES_H
