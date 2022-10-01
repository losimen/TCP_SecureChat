#ifndef CLIENTTYPES_H
#define CLIENTTYPES_H

#include <QtGlobal>
#include <QString>
#include <QJsonObject>

#include "statuscodes.h"


namespace ClientTypes
{
// Param with '_' at the beginning are additional information parameters
// and not used for serialazation and parsing

QString putTagInQuotes(const QString &name);
QString putStrInQuotes(const QString &name);


struct LogIn
{
    StatusCodesInterface statusCode;
    QString accessToken;

    QByteArray serializeData() const;
};


struct SignUp
{
    StatusCodesInterface statusCode;
    QString accessToken;

    QByteArray serializeData() const;
};


struct Error
{
    StatusCodesInterface statusCode;
    QString what;

    QByteArray serializeData() const;
};


struct CreateChat
{
    StatusCodesInterface statusCode;
    qint64 chatId;

    QByteArray serializeData() const;
};


struct AddMember
{
    StatusCodesInterface statusCode;

    QByteArray serializeData() const;
};


struct SendMessage
{
    StatusCodesInterface statusCode;

    QByteArray serializeData() const;
};

}

#endif // CLIENTTYPES_H
