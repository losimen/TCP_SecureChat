#include <QThread>
#include <QString>

#include "sqldatabase.h"
#include "dberrors.h"


void SQLDatabase::validateIsOpen()
{
    if (!SQLDatabase::db.isOpen())
    {
        qDebug() << db.lastError();
        throw DBErrors::Open("Error in connecting to the DB please contact admin.");
    }

}


void SQLDatabase::execQuery(QSqlQuery &query)
{
    if (!query.exec())
    {
        qDebug() << query.lastError();
        throw DBErrors::Exec("Error in executing request please contact admin.");
    }
}


SQLDatabase::SQLDatabase()
{
    qint32 *a = (int*)QThread::currentThreadId();
    SQLDatabase::db = QSqlDatabase::addDatabase("QMYSQL", QString::number((*a)));

    db.setHostName("localhost");
    db.setDatabaseName("SecureChat");
    db.setUserName("root");
    db.setPassword("zTmUHsbEKZZlWhfofM");

    db.open();
}


qint64 SQLDatabase::insertUser(const QString &username, const QString &password)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("INSERT INTO Users (Username, Password) "
                  "VALUES (:Username, :Password)");
    query.bindValue(":Username", username);
    query.bindValue(":Password", password);

    SQLDatabase::execQuery(query);

    return SQLDatabase::getUserIdByUsername(username);
}


qint64 SQLDatabase::insertChat(const qint64 &userId, const QString &chatName)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("INSERT INTO Chats (CreatorID, ChatName) "
                  "VALUES (:CreatorID, :ChatName)");
    query.bindValue(":CreatorID", userId);
    query.bindValue(":ChatName", chatName);

    SQLDatabase::execQuery(query);

    return SQLDatabase::getChatId(userId, chatName);
}


void SQLDatabase::insertMember(const qint64 &chatId, const qint64 &memberId)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("INSERT INTO Members (MemberID, ChatID) "
                  "VALUES (:MemberID, :ChatID)");
    query.bindValue(":MemberID", memberId);
    query.bindValue(":ChatID", chatId);

    SQLDatabase::execQuery(query);
}


void SQLDatabase::insertMessage(const qint64 &chatId, const qint64 &senderId, const QString &msgText)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("INSERT INTO Messages (SenderID, ChatID, MsgText) "
                  "VALUES (:SenderID, :ChatID, :MsgText)");
    query.bindValue(":SenderID", senderId);
    query.bindValue(":ChatID", chatId);
    query.bindValue(":MsgText", msgText);

    SQLDatabase::execQuery(query);
}


qint64 SQLDatabase::getUserIdByAuth(const QString &username, const QString &password)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("SELECT ID FROM Users WHERE Username = :Username AND Password = :Password");
    query.bindValue(":Username", username);
    query.bindValue(":Password", password);

    SQLDatabase::execQuery(query);

    if (!query.first())
        throw DBErrors::GetValue("There is no such record");

    return query.value(0).toInt();
}


qint64 SQLDatabase::getUserIdByUsername(const QString &username)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("SELECT ID FROM Users WHERE Username = :Username");
    query.bindValue(":Username", username);

    SQLDatabase::execQuery(query);

    if (!query.first())
        throw DBErrors::GetValue("There is no such record");

    return query.value(0).toInt();
}


qint64 SQLDatabase::getUserIdByAccessToken(const QString &accessToken)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("SELECT UserID FROM AccessTokens WHERE AccessToken = :AccessToken");
    query.bindValue(":AccessToken", accessToken);

    SQLDatabase::execQuery(query);

    if (!query.first())
        throw DBErrors::GetValue("There is no such record");

    return query.value(0).toInt();
}


QString SQLDatabase::generateAccessToken(const qint64 userId)
{
    // TODO: use SHA256
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);
    QString accessToken = "accessToken_" + QString::number(userId);

    query.prepare("INSERT INTO AccessTokens (AccessToken, UserID) "
                  "VALUES (:AccessToken, :UserID)");

    query.bindValue(":AccessToken", accessToken);
    query.bindValue(":UserID", userId);

    SQLDatabase::execQuery(query);

    return accessToken;
}


QString SQLDatabase::getUserAccessToken(const qint64 userId)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("SELECT AccessToken FROM AccessTokens WHERE UserID = :UserID");
    query.bindValue(":UserID", userId);

    SQLDatabase::execQuery(query);

    if (!query.first())
        throw DBErrors::GetValue("There is no such record");

    return query.value(0).toString();
}


DBModelUser SQLDatabase::getUserInfo(const qint64 &userId)
{
    DBModelUser userModel;
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("SELECT * FROM Users WHERE ID = :UserID");
    query.bindValue(":UserID", userId);

    SQLDatabase::execQuery(query);

    if (!query.first())
        throw DBErrors::GetValue("There is no such record");

    userModel.id = query.value(0).toInt();
    userModel.username = query.value(1).toString();
    userModel.password = query.value(2).toString();
    userModel.createdAt = query.value(3).toString();

    return userModel;
}


DBModelChat SQLDatabase::getChatInfo(const qint64 &chatId)
{
    DBModelChat chatModel;
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("SELECT * FROM Chats WHERE ID = :ChatID");
    query.bindValue(":ChatID", chatId);

    SQLDatabase::execQuery(query);

    if (!query.first())
        throw DBErrors::GetValue("There is no such record");

    chatModel.id = query.value(0).toInt();
    chatModel.creatorId = query.value(1).toInt();
    chatModel.chatName = query.value(2).toString();
    chatModel.createdAt = query.value(3).toString();

    return chatModel;
}


DBModelMessage SQLDatabase::getMessageInfo(const qint64 &messageId)
{
    DBModelMessage messageModel;
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("SELECT * FROM Messages WHERE ID = :MessageID");
    query.bindValue(":ChatID", messageId);

    SQLDatabase::execQuery(query);

    if (!query.first())
        throw DBErrors::GetValue("There is no such record");

    messageModel.id = query.value(0).toInt();
    messageModel.senderId = query.value(1).toInt();
    messageModel.chatId = query.value(2).toInt();
    messageModel.msgText = query.value(3).toString();
    messageModel.createdAt = query.value(4).toString();

    return messageModel;
}

MessageList SQLDatabase::getMessageList(const qint64 &chatId, const qint64 &offset)
{
    // TODO: in future use offset
    MessageList messageList;
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);
    query.prepare("SELECT * FROM Messages WHERE ChatID = :ChatID");
    query.bindValue(":ChatID", chatId);

    SQLDatabase::execQuery(query);

    while (query.next())
    {
        DBModelMessage messageModel;

        messageModel.id = query.value(0).toInt();
        messageModel.senderId = query.value(1).toInt();
        messageModel.chatId = query.value(2).toInt();
        messageModel.msgText = query.value(3).toString();
        messageModel.createdAt = query.value(4).toString();

        messageList.push_back(messageModel);
    }

    return messageList;
}


qint64 SQLDatabase::getChatId(const qint64 &userId, const QString &chatName)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("SELECT ID FROM Chats WHERE CreatorID = :CreatorID AND ChatName = :ChatName");
    query.bindValue(":CreatorID", userId);
    query.bindValue(":ChatName", chatName);

    SQLDatabase::execQuery(query);

    if (!query.first())
        throw DBErrors::GetValue("There is no such record");

    return query.value(0).toInt();
}


SQLDatabase::~SQLDatabase()
{
    qint32 *a = (int*)QThread::currentThreadId();

    db.close();
    db = QSqlDatabase();

    QSqlDatabase::removeDatabase(QString::number((*a)));
}
