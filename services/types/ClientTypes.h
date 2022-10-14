#pragma once

#include <QtGlobal>
#include <QString>
#include <QJsonObject>
#include <QVector>

#include "itype.h"


namespace ClientTypes
{

struct LogIn: public IType
{
    LogIn() = default;
    LogIn(QJsonObject &obj);

    StatusCodesWorker statusCode;
    QString accessToken;

    QByteArray serializeData() const override;
};


struct SignUp: public IType
{
    StatusCodesWorker statusCode;
    QString accessToken;

    QByteArray serializeData() const override;
};


struct Error: public IType
{
    StatusCodesWorker statusCode;
    QString what;

    QByteArray serializeData() const override;
};


struct CreateChat: public IType
{
    StatusCodesWorker statusCode;
    qint64 chatId;

    QByteArray serializeData() const override;
};


struct AddMember: public IType
{
    StatusCodesWorker statusCode;

    QByteArray serializeData() const override;
};


struct SendMessage: public IType
{
    StatusCodesWorker statusCode;

    QByteArray serializeData() const override;
};


struct GetMessageList: public IType
{
    StatusCodesWorker statusCode;
    QVector<DBModelMessage> messageList;

    QByteArray serializeData() const override;
};


struct GetChatList : public IType
{
    StatusCodesWorker statusCode;

    QVector<DBModelChat> chatList;

    QByteArray serializeData() const override;
};


struct GetUpdates : public IType
{
    StatusCodesWorker statusCode;
    bool isBackground;

    QVector<DBModelMessage> messageList;

    QByteArray serializeData() const override;
};


struct GetPubKey : public IType
{
    StatusCodesWorker statusCode;
    QString pubKey;

    QByteArray serializeData() const override;
};


}
