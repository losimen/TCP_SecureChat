#ifndef REQUESTVALIDATOR_H
#define REQUESTVALIDATOR_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#include "servertypes.h"
#include "sqldatabase.h"


class RequestValidator
{
public:
    RequestValidator();

    static QJsonObject format(const QByteArray &buffer);

    static ServerTypes::LogIn logIn(SQLDatabase &db, const QJsonObject &buffer);
    static ServerTypes::SignUp signUp(SQLDatabase &db, const QJsonObject &buffer);
    static ServerTypes::CreateChat createChat(SQLDatabase &db, const QJsonObject &buffer);
};

#endif // REQUESTVALIDATOR_H
