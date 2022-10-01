#ifndef REQUESTVALIDATOR_H
#define REQUESTVALIDATOR_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#include "servertypes.h"
#include "sqldatabase.h"


class RequestValidator
{
private:
    static qint64 validateAccessToken(SQLDatabase &db, const QString &accessToken);
    static qint64 validateUsername(SQLDatabase &db, const QString &username);
    static qint64 validateChatName(SQLDatabase &db, const qint64 userId, const QString &chatName);

public:
    RequestValidator();

    static QJsonObject format(const QByteArray &buffer);

    static ServerTypes::LogIn logIn(SQLDatabase &db, const QJsonObject &buffer);
    static ServerTypes::SignUp signUp(SQLDatabase &db, const QJsonObject &buffer);
    static ServerTypes::CreateChat createChat(SQLDatabase &db, const QJsonObject &buffer);
    static ServerTypes::AddMember addMember(SQLDatabase &db, const QJsonObject &buffer);
};

#endif // REQUESTVALIDATOR_H
