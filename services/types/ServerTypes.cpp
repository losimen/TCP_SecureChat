#include "servertypes.h"
#include "requestmethods.h"

using namespace ServerTypes;


QByteArray LogIn::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"method\": %1,\n"
                     "\"username\": %2,\n"
                     "\"password\": %3\n"
                     "}").arg(putStrInQuotes(RequestMethods::logIn),
                              putStrInQuotes(username),
                              putStrInQuotes(password));

    return result.toUtf8();
}


QByteArray SignUp::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"method\": %1,\n"
                     "\"username\": %2,\n"
                     "\"password\": %3\n"
                     "}").arg(putStrInQuotes(RequestMethods::signUp),
                              putStrInQuotes(username),
                              putStrInQuotes(password));

    return result.toUtf8();
}


QByteArray CreateChat::serializeData() const
{
    return QByteArray();
}


QByteArray AddMember::serializeData() const
{
    return QByteArray();
}


QByteArray SendMessage::serializeData() const
{
    return QByteArray();
}


QByteArray GetMessageList::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"method\": %1,\n"
                     "\"accessToken\": %2,\n"
                     "\"chatId\": %3,\n"
                     "\"offset\": %4\n"
                     "}").arg(putStrInQuotes(RequestMethods::getMessageList),
                              putStrInQuotes(accessToken),
                              QString::number(chatId),
                              QString::number(offset));

    return result.toUtf8();}


QByteArray GetChatList::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"method\": %1,\n"
                     "\"accessToken\": %2,\n"
                     "\"offset\": %3\n"
                     "}").arg(putStrInQuotes(RequestMethods::getChatList),
                              putStrInQuotes(accessToken),
                              QString::number(offset));

    return result.toUtf8();
}
