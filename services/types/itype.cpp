#include "itype.h"


QString IType::putTagInQuotes(const QString &name) const
{
    return QString("\n\"" + name + "\": ");
}


QString IType::putStrInQuotes(const QString &name) const
{
    return QString("\"" + name + "\"");
}


QString IType::serializeMsgList(MessageList &list) const
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


QString IType::serializeChatList(ChatList &list) const
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


