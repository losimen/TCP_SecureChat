#include "servertypes.h"
#include "requestmethods.h"

using namespace ServerTypes;


QByteArray LogIn::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"method\": \"%1\",\n"
                     "\"username\": \"%2\",\n"
                     "\"password\": \"%3\"\n"
                     "}").arg(RequestMethods::logIn,
                              username,
                              password);

    return result.toUtf8();
}


QByteArray SignUp::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"method\": \"%1\",\n"
                     "\"username\": \"%2\",\n"
                     "\"password\": \"%3\"\n"
                     "}").arg(RequestMethods::signUp,
                              username,
                              password);

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
    QString result;

    result = QString("{\n"
                     "\"method\": \"%1\",\n"
                     "\"accessToken\": \"%2\",\n"
                     "\"chatId\": %3,\n"
                     "\"msgText\": \"%4\"\n"
                     "}").arg(RequestMethods::sendMessage,
                              accessToken,
                              QString::number(chatId),
                              msgText);

    return result.toUtf8();
}


QByteArray GetMessageList::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"method\": \"%1\",\n"
                     "\"accessToken\": \"%2\",\n"
                     "\"chatId\": %3,\n"
                     "\"offset\": %4\n"
                     "}").arg(RequestMethods::getMessageList,
                              accessToken,
                              QString::number(chatId),
                              QString::number(offset));

    return result.toUtf8();}


QByteArray GetChatList::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"method\": \"%1\",\n"
                     "\"accessToken\": \"%2\",\n"
                     "\"offset\": %3\n"
                     "}").arg(RequestMethods::getChatList,
                              accessToken,
                              QString::number(offset));

    return result.toUtf8();
}


QByteArray GetUpdates::serializeData() const
{
    return QByteArray();
}
