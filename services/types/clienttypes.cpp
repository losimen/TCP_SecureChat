#include <cstdio>

#include "clienttypes.h"

using namespace ClientTypes;


QByteArray LogIn::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"statusCode\": %1,\n"
                     "\"accessToken\": \"%2\"\n"
                     "}").arg(QString::number(statusCode.getCurrentStatusCode()),
                              accessToken);

    return result.toUtf8();
}


QByteArray SignUp::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"statusCode\": %1,\n"
                     "\"accessToken\": \"%2\"\n"
                     "}").arg(QString::number(statusCode.getCurrentStatusCode()),
                              accessToken);

    return result.toUtf8();
}


QByteArray Error::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"statusCode\": %1,\n"
                     "\"msg\": \"%2\"\n"
                     "}").arg(QString::number(statusCode.getCurrentStatusCode()),
                              what);

    return result.toUtf8();
}

QByteArray CreateChat::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"statusCode\": %1,\n"
                     "\"chatID\": %2\n"
                     "}").arg(QString::number(statusCode.getCurrentStatusCode()),
                              QString::number(chatId));

    return result.toUtf8();
}

QByteArray AddMember::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"statusCode\": %1\n"
                     "}").arg(QString::number(statusCode.getCurrentStatusCode()));

    return result.toUtf8();
}

QByteArray SendMessage::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"statusCode\": %1\n"
                     "}").arg(QString::number(statusCode.getCurrentStatusCode()));

    return result.toUtf8();
}

QByteArray GetMessageList::serializeData() const
{
    QString result;
    DBMessageList vec = GetMessageList::messageList;

    result = QString("{\n"
                     "\"statusCode\": %1,\n"
                     "\"messageList\": [%2]\n"
                     "}").arg(QString::number(statusCode.getCurrentStatusCode()),
                              serializeMsgList(vec));

    return result.toUtf8();
}


QByteArray GetChatList::serializeData() const
{
    QString result;
    DBChatList vec = GetChatList::chatList;

    result = QString("{\n"
                     "\"statusCode\": %1,\n"
                     "\"chatList\": [%2]\n"
                     "}").arg(QString::number(statusCode.getCurrentStatusCode()),
                              serializeChatList(vec));

    return result.toUtf8();
}


QByteArray GetUpdates::serializeData() const
{
    QString result;
    DBMessageList vec = messageList;

    result = QString("{\n"
                     "\"statusCode\": %1,\n"
                     "\"isUpdate\": %2,\n"
                     "\"messageList\": [%3]\n"
                     "}").arg(QString::number(statusCode.getCurrentStatusCode()),
                              QString::number(1),
                              serializeMsgList(vec));

    return result.toUtf8();
}


QByteArray GetPubKey::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"statusCode\": %1,\n"
                     "\"pubKey\": \"%2\"\n"
                     "}").arg(QString::number(statusCode.getCurrentStatusCode()),
                                                  pubKey);

    return result.toUtf8();
}
