#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include "servertypes.h"


class InputValidator
{
public:
    InputValidator();

    static ServerTypes::LogIn logIn(const QString &username, const QString &password);

};

#endif // INPUTVALIDATOR_H
