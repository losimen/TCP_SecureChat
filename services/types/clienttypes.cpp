#include "clienttypes.h"

using namespace ClientTypes;


QString ClientTypes::putTagInQuotes(const QString &name) {
    return QString("\n\"" + name + "\": ");
}


QString ClientTypes::putStrInQuotes(const QString &name) {
    return QString("\"" + name + "\"");
}


void LogIn::parseData(const StatusCodes &statusCode, const QString &accessToken)
{
    LogIn::statusCode = statusCode;
    LogIn::accessToken = accessToken;
}


QByteArray LogIn::serializeData() const
{
    QString result;

    result = "{";
    result += putTagInQuotes("statusCode") + QString::number(LogIn::statusCode.getCurrentStatusCode()) + ",";
    result += putTagInQuotes("asccessToken") + putStrInQuotes(LogIn::accessToken);
    result += "\n}\n";

    return result.toUtf8();
}


void SignUp::parseData(const StatusCodes &statusCode, const QString &accessToken)
{
    SignUp::statusCode = statusCode;
    SignUp::accessToken = accessToken;
}


void Error::parseData(const StatusCodes &statusCode, const QString &what)
{
    Error::statusCode = statusCode;
    Error::what = what;
}


QByteArray Error::serializeData() const
{
    QString result;

    result = "{" ;
    result += putTagInQuotes("statusCode") + QString::number(Error::statusCode.getCurrentStatusCode()) + ",";
    result += putTagInQuotes("msg") + putStrInQuotes(what);
    result += "\n}\n";

    return result.toUtf8();
}
