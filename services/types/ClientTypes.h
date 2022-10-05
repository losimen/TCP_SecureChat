#ifndef CLIENTTYPES_H
#define CLIENTTYPES_H

#include <QtGlobal>
#include <QString>
#include <QJsonObject>
#include <QVector>

#include "statuscodes.h"
#include "dbmodelmessage.h"
#include "dbmodeluser.h"
#include "dbmodelchat.h"


namespace ClientTypes
{
QString putTagInQuotes(const QString &name);
QString putStrInQuotes(const QString &name);

QString serializeMsgList(MessageList &list);
QString serializeChatList(ChatList &list);

// Param with '_' at the beginning are additional information parameters
// and not used for serialazation and parsing

struct LogIn
{
    StatusCodesWorker statusCode;
    QString accessToken;

    QByteArray serializeData() const;
};


struct SignUp
{
    StatusCodesWorker statusCode;
    QString accessToken;

    QByteArray serializeData() const;
};


struct Error
{
    StatusCodesWorker statusCode;
    QString what;

    QByteArray serializeData() const;
};


struct CreateChat
{
    StatusCodesWorker statusCode;
    qint64 chatId;

    QByteArray serializeData() const;
};


struct AddMember
{
    StatusCodesWorker statusCode;

    QByteArray serializeData() const;
};


struct SendMessage
{
    StatusCodesWorker statusCode;

    QByteArray serializeData() const;
};


struct GetMessageList
{
    StatusCodesWorker statusCode;
    QVector<DBModelMessage> messageList;

    QByteArray serializeData() const;
};


struct GetChatList {
    StatusCodesWorker statusCode;

    QVector<DBModelChat> chatList;

    QByteArray serializeData() const;
};

}

#endif // CLIENTTYPES_H
