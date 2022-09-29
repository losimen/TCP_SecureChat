#ifndef CLIENTTYPES_H
#define CLIENTTYPES_H

#include <QtGlobal>
#include <QString>
#include <QJsonObject>

#include "statuscodes.h"


namespace ClientTypes
{
QString putTagInQuotes(const QString &name);


struct LogIn
{
    StatusCodesInterface statusCode;
    QString accessToken;

    void parseData(const StatusCodes &statusCode, const QString &accessToken);
    QByteArray serializeData() const;
};


struct SignUp
{
    StatusCodesInterface statusCode;
    QString accessToken;

    void parseData(const StatusCodes &statusCode, const QString &accessToken);
    QByteArray serializeData() const;
};


struct Error
{
    StatusCodesInterface statusCode;
    QString what;

    void parseData(const StatusCodes &statusCode, const QString &what);
    QByteArray serializeData() const;
};

}

#endif // CLIENTTYPES_H
