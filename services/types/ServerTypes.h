#ifndef SERVERTYPES_H
#define SERVERTYPES_H

#include <QtGlobal>
#include <QString>
#include <QJsonObject>


namespace ServerTypes
{
// Param with '_' at the beginning are additional information parameters
// and not used for serialazation and parsing

struct LogIn
{
    QString username;
    QString password;

    qint64 _userId;

    QByteArray serializeData() const;

};


struct SignUp
{
    QString username;
    QString password;

    QByteArray serializeData() const;
};


struct CreateChat
{
    QString accessToken;
    QString chatName;

    qint64 _creatorId;

    QByteArray serializeData() const;
};


struct AddMember
{
    QString accessToken;
    QString memberToAddUsername;
    QString chatName;

    qint64 _userIdToAdd;
    qint64 _chatId;

    QByteArray serializeData() const;
};


}




#endif // SERVERTYPES_H
