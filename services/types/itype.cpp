#include "itype.h"


QString IType::serializeMsgList(DBMessageList &list) const
{
    QString result;
    const auto VEC_END = list.end();
    const auto VEC_END_DEC = list.end() - 1;

    for (auto it = list.begin(); it != VEC_END; it++)
    {
        result += QString("{\n"
                          "\"id\": %1,\n"
                          "\"senderId\": %2,\n"
                          "\"senderUsername\": \"%3\",\n"
                          "\"chatId\": %4,\n"
                          "\"msgText\": \"%5\",\n"
                          "\"createdAt\": \"%6\"\n"
                          "}").arg(QString::number(it->id),
                                   QString::number(it->senderId),
                                   it->sendeUsername,
                                   QString::number(it->chatId),
                                   it->msgText,
                                   it->createdAt);

        if (it != VEC_END_DEC)
            result += ",";

        result += "\r\n";
    }

    return result;
}


QString IType::serializeChatList(DBChatList &list) const
{
    QString result;
    const auto VEC_END = list.end();
    const auto VEC_END_DEC = list.end() - 1;

    for (auto it = list.begin(); it != VEC_END; it++)
    {
        result += QString("{\n"
                          "\"id\": %1,\n"
                          "\"chatName\": \"%3\",\n"
                          "\"creatorId\": %4,\n"
                          "\"createdAt\": \"%6\"\n"
                          "}").arg(QString::number(it->id),
                                   it->chatName,
                                   QString::number(it->creatorId),
                                   it->createdAt);

        if (it != VEC_END_DEC)
            result += ",";

        result += "\r\n";
    }

    return result;
}


