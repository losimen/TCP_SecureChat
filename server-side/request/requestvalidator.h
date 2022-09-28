#ifndef REQUESTVALIDATOR_H
#define REQUESTVALIDATOR_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#include "servertypes.h"


class RequestValidator
{
public:
    RequestValidator();

    static QJsonObject format(const QByteArray &buffer);

    static ServerTypes::LogIn logIn(const QJsonObject &buffer);
    static ServerTypes::SignUp signUp(const QJsonObject &buffer);
};

#endif // REQUESTVALIDATOR_H
