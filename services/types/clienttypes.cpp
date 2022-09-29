#include "clienttypes.h"

using namespace ClientTypes;


void LogIn::parseData(const StatusCodes &statusCode, const QString &accessToken)
{
    LogIn::statusCode = statusCode;
    LogIn::accessToken = accessToken;
}


QByteArray LogIn::serializeData() const
{
   QString result;

   result = "{\n statusCode: " + QString::number(LogIn::statusCode.getCurrentStatusCode()) + ",\n";
   result += LogIn::accessToken + "}\n";

   return result.toUtf8();
}


void SignUp::parseData(const StatusCodes &statusCode, const QString &accessToken)
{
    SignUp::statusCode = statusCode;
    SignUp::accessToken = accessToken;
}


void InvalidFormat::parseData(const StatusCodes &statusCode, const QString &what)
{
    InvalidFormat::statusCode = statusCode;
    InvalidFormat::what = what;
}


QByteArray InvalidFormat::serializeData() const
{
    QString result;

    result = "{\n statusCode: " + QString::number(InvalidFormat::statusCode.getCurrentStatusCode())  + ",\n";
    result += " msg: " + InvalidFormat::what + "}\n";

    return result.toUtf8();
}


void MissingAgument::parseData(const StatusCodes &statusCode, const QString &what)
{
    MissingAgument::statusCode = statusCode;
    MissingAgument::what = what;
}


QByteArray MissingAgument::serializeData() const
{
    QString result;

    result = "{\n statusCode: " + QString::number(MissingAgument::statusCode.getCurrentStatusCode())  + ",\n";
    result += " msg: " + MissingAgument::what + "}\n";

    return result.toUtf8();
}


void InternalError::parseData(const StatusCodes &statusCode, const QString &what)
{
    InternalError::statusCode = statusCode;
    InternalError::what = what;
}


QByteArray InternalError::serializeData() const
{
    QString result;

    result = "{\n statusCode: " + QString::number(InternalError::statusCode.getCurrentStatusCode())  + ",\n";
    result += " msg: " + InternalError::what + "}\n";

    return result.toUtf8();
}
