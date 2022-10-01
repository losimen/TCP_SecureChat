#include "clienttypes.h"

using namespace ClientTypes;


QString ClientTypes::putTagInQuotes(const QString &name) {
    return QString("\n\"" + name + "\": ");
}


QString ClientTypes::putStrInQuotes(const QString &name) {
    return QString("\"" + name + "\"");
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



QByteArray SignUp::serializeData() const
{
    QString result;

    result = "{";
    result += putTagInQuotes("statusCode") + QString::number(SignUp::statusCode.getCurrentStatusCode()) + ",";
    result += putTagInQuotes("asccessToken") + putStrInQuotes(SignUp::accessToken);
    result += "\n}\n";

    return result.toUtf8();
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

QByteArray CreateChat::serializeData() const
{
    QString result;

    result = "{" ;
    result += putTagInQuotes("statusCode") + QString::number(CreateChat::statusCode.getCurrentStatusCode()) + ",";
    result += putTagInQuotes("chatID") + QString::number(CreateChat::chatId);
    result += "\n}\n";

    return result.toUtf8();
}

QByteArray AddMember::serializeData() const
{
    QString result;

    result = "{" ;
    result += putTagInQuotes("statusCode") + QString::number(AddMember::statusCode.getCurrentStatusCode());
    result += "\n}\n";

    return result.toUtf8();
}

QByteArray SendMessage::serializeData() const
{
    QString result;

    result = "{" ;
    result += putTagInQuotes("statusCode") + QString::number(SendMessage::statusCode.getCurrentStatusCode());
    result += "\n}\n";

    return result.toUtf8();
}
