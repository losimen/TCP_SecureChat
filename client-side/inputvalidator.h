#pragma once

#include "servertypes.h"


class InputValidator
{
public:
    InputValidator();

    static ServerTypes::LogIn logIn(const QString &username, const QString &password);
    static ServerTypes::SignUp signUp(const QString &username, const QString &password_1, const QString &password_2);
    static ServerTypes::SendMessage sendMessage(const QString &msgText);
};
