#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <QtSql>
#include <QDebug>
#include <QString>

#include "dbmodelchat.h"
#include "dbmodeluser.h"
#include "dbmodelmessage.h"


class SQLDatabase
{
private:
    QSqlDatabase db;
    bool ok;

    void validateIsOpen();
    void execQuery(QSqlQuery &query);

public:
    SQLDatabase();

    const qint64 insertUser(const QString &username, const QString &password);
    const qint64 insertChat(const qint64 &userId, const QString &chatName);
    void insertMember(const qint64 &chatId, const qint64 &memberId);
    void insertMessage(const qint64 &chatId, const qint64 &senderId, const QString &msgText);

    const qint64 getUserIdByAuth(const QString &username, const QString &password);
    const qint64 getUserIdByUsername(const QString &username);
    const qint64 getUserIdByAccessToken(const QString &accessToken);
    const QString getUserAccessToken(const qint64 userId);

    const DBModelUser getUserInfo(const qint64 &userId);
    const DBModelChat getChatInfo(const qint64 &chatId);
    const DBModelMessage getMessageInfo(const qint64 &messageId);

    const MessageList getMessageList(const qint64 &chatId, const qint64 &offset);
    const ChatList getChatList(const qint64 &userId, const qint64 &offset);

    const qint64 getChatId(const qint64 &userId, const QString &chatName);

    const QString generateAccessToken(const qint64 userId);

    ~SQLDatabase();
};

#endif // SQLDATABASE_H
