#include "servertypes.h"

using namespace ServerTypes;

void LogIn::parseData(const QString &username, const QString &password)
{
    LogIn::username = username;
    LogIn::password = password;
}


void SignUp::parseData(const QString &username, const QString &password)
{
    SignUp::username = username;
    SignUp::password = password;
}

