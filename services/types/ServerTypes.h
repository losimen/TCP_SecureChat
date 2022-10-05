#pragma once

#include <QString>
#include <QJsonObject>

#include "itype.h"


namespace ServerTypes
{

struct LogIn: public IType
{
    LogIn() = default;
    ~LogIn() = default;

    QString username;
    QString password;

    qint64 _userId;

    QByteArray serializeData() const override;
};


struct SignUp: public IType
{
    QString username;
    QString password;

    QByteArray serializeData() const override;
};


struct CreateChat: public IType
{
    QString accessToken;
    QString chatName;

    qint64 _creatorId;

    QByteArray serializeData() const override;
};


struct AddMember: public IType
{
    QString accessToken;
    QString memberToAddUsername;
    QString chatName;

    qint64 _userIdToAdd;
    qint64 _chatId;

    QByteArray serializeData() const override;
};


struct SendMessage: public IType
{
    QString accessToken;
    QString msgText;
    qint64 chatId;

    qint64 _senderId;

    QByteArray serializeData() const override;
};


struct GetMessageList: public IType
{
    QString accessToken;
    qint64 offset;
    qint64 chatId;

    QByteArray serializeData() const override;
};


struct GetChatList: public IType
{
    QString accessToken;
    qint64 offset;

    qint64 _userId;

    QByteArray serializeData() const override;
};


}
