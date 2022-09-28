#include "clienttypes.h"

using namespace ClientTypes;


void LogIn::parseData(const StatusCodes &statusCode, const QString &accessToken)
{
//    LogIn::statusCode = statusCode;
    LogIn::accessToken = accessToken;
}


QByteArray LogIn::serializeData() const
{
   QString result;

   result = "{" + LogIn::statusCode.getCurrentStatusCode() + "}\n";
}


void SignUp::parseData(const StatusCodes &statusCode, const QString &accessToken)
{
//    SignUp::statusCode;
    SignUp::accessToken = accessToken;
}
