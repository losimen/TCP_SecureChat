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

    qint64 insertUser(const QString &username, const QString &password);
    qint64 insertChat(const qint64 &userId, const QString &chatName);
    void insertMember(const qint64 &chatId, const qint64 &memberId);
    void insertMessage(const qint64 &chatId, const qint64 &senderId, const QString &msgText);

    qint64 getUserIdByAuth(const QString &username, const QString &password);
    qint64 getUserIdByUsername(const QString &username);
    qint64 getUserIdByAccessToken(const QString &accessToken);
    QString getUserAccessToken(const qint64 userId);

    DBModelUser getUserInfo(const qint64 &userId);
    DBModelChat getChatInfo(const qint64 &chatId);
    DBModelMessage getMessageInfo(const qint64 &messageId);

    qint64 getChatId(const qint64 &userId, const QString &chatName);

    QString generateAccessToken(const qint64 userId);

    ~SQLDatabase();
};

#endif // SQLDATABASE_H
