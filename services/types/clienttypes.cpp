#include <cstdio>

#include "clienttypes.h"

using namespace ClientTypes;


QByteArray LogIn::serializeData() const
{
    QString result;

    result = "{";
    result += putTagInQuotes("statusCode") + QString::number(LogIn::statusCode.getCurrentStatusCode()) + ",";
    result += putTagInQuotes("accessToken") + putStrInQuotes(LogIn::accessToken);
    result += "\n}\n";

    return result.toUtf8();
}


QByteArray SignUp::serializeData() const
{
    QString result;

    result = "{";
    result += putTagInQuotes("statusCode") + QString::number(SignUp::statusCode.getCurrentStatusCode()) + ",";
    result += putTagInQuotes("accessToken") + putStrInQuotes(SignUp::accessToken);
    result += "\n}\n";

    return result.toUtf8();
}


QByteArray Error::serializeData() const
{
    QString result;

    result = QString("{\n"
                     "\"statusCode\": %1,\n"
                     "\"msg\": %2\n"
                     "}").arg(QString::number(Error::statusCode.getCurrentStatusCode()),
                              putStrInQuotes(what));

    return result.toUtf8();
}

QByteArray CreateChat::serializeData() const
{
    QString result;

    result = "{";
    result += putTagInQuotes("statusCode") + QString::number(CreateChat::statusCode.getCurrentStatusCode()) + ",";
    result += putTagInQuotes("chatID") + QString::number(CreateChat::chatId);
    result += "\n}\n";

    return result.toUtf8();
}

QByteArray AddMember::serializeData() const
{
    QString result;

    result = "{";
    result += putTagInQuotes("statusCode") + QString::number(AddMember::statusCode.getCurrentStatusCode());
    result += "\n}\n";

    return result.toUtf8();
}

QByteArray SendMessage::serializeData() const
{
    QString result;

    result = "{";
    result += putTagInQuotes("statusCode") + QString::number(SendMessage::statusCode.getCurrentStatusCode());
    result += "\n}\n";

    return result.toUtf8();
}

QByteArray GetMessageList::serializeData() const
{
    // {"messageList": [{"data": 1, "text": "Hello"}, {"data": 1, "text": "world!"}]}
    QString result;
    MessageList vec = GetMessageList::messageList;

    result = "{";
    result += putTagInQuotes("statusCode") + QString::number(GetMessageList::statusCode.getCurrentStatusCode()) + ",";
    result += putTagInQuotes("messageList") + serializeMsgList(vec);
    result += "}\n";

    return result.toUtf8();
}


QByteArray GetChatList::serializeData() const
{
    QString result;
    ChatList vec = GetChatList::chatList;

    result = "{";
    result += putTagInQuotes("statusCode") + QString::number(GetChatList::statusCode.getCurrentStatusCode()) + ",";
    result += putTagInQuotes("chatList") + serializeChatList(vec);
    result += "}\n";

    return result.toUtf8();
}
