#include "clienttypes.h"


using namespace ClientTypes;


QString ClientTypes::putTagInQuotes(const QString &name)
{
    return QString("\n\"" + name + "\": ");
}


QString ClientTypes::putStrInQuotes(const QString &name)
{
    return QString("\"" + name + "\"");
}


QString ClientTypes::serializeMsgList(MessageList &list)
{
    QString result;
    const auto VEC_END = list.end();
    const auto VEC_END_DEC = list.end() - 1;

    result = "[";
    for (auto it = list.begin(); it != VEC_END; it++)
    {
        result += "{";
        result += putTagInQuotes("id") + QString::number(it->id);
        result += putTagInQuotes("senderId") + QString::number(it->senderId);
        result += putTagInQuotes("chatId") + QString::number(it->chatId);
        result += putTagInQuotes("msgText") + putStrInQuotes(it->msgText);
        result += putTagInQuotes("createdAt") + putStrInQuotes(it->createdAt);
        result += "\r\n}";

        if (it != VEC_END_DEC)
            result += ",";

        result += "\r\n";
    }
    result += "]\n";

    return result;
}


QString ClientTypes::serializeChatList(ChatList &list)
{
    QString result;
    const auto VEC_END = list.end();
    const auto VEC_END_DEC = list.end() - 1;

    result = "[";
    for (auto it = list.begin(); it != VEC_END; it++)
    {
        result += "{";
        result += putTagInQuotes("id") + QString::number(it->id);
        result += putTagInQuotes("chatName") + putStrInQuotes(it->chatName);
        result += putTagInQuotes("creatorId") + QString::number(it->creatorId);
        result += putTagInQuotes("createdAt") + putStrInQuotes(it->createdAt);
        result += "\r\n}";

        if (it != VEC_END_DEC)
            result += ",";

        result += "\r\n";
    }
    result += "]\n";

    return result;
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

    result = "{";
    result += putTagInQuotes("statusCode") + QString::number(Error::statusCode.getCurrentStatusCode()) + ",";
    result += putTagInQuotes("msg") + putStrInQuotes(what);
    result += "\n}\n";

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
