#include "sqldatabase.h"
#include "dberrors.h"
#include "security.h"
#include "base64.h"


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


const qint64 SQLDatabase::insertUser(const QString &username, const QString &password)
{
    SQLDatabase::validateIsOpen();

    Security security("keys/server");
    auto shaPass = QString::fromUtf8(security.decryptPrivateMSG(base64_decode(password.toStdString())).c_str());
    qDebug() << "shaPass in insertUser:" << shaPass;

    QSqlQuery query(SQLDatabase::db);
    query.prepare("INSERT INTO Users (Username, Password) "
                  "VALUES (:Username, :Password)");
    query.bindValue(":Username", username);
    query.bindValue(":Password", shaPass);
    SQLDatabase::execQuery(query);

    return SQLDatabase::getUserIdByUsername(username);
}


const qint64 SQLDatabase::insertChat(const qint64 &userId, const QString &chatName)
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


const qint64 SQLDatabase::getUserIdByAuth(const QString &username, const QString &password)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    Security security("keys/server");
    auto shaPass = QString::fromUtf8(security.decryptPrivateMSG(base64_decode(password.toStdString())).c_str());

    qDebug() << "shaPass in gatUserIdByAuth:" << shaPass;

    query.prepare("SELECT ID FROM Users WHERE Username = :Username AND Password = :Password");
    query.bindValue(":Username", username);
    query.bindValue(":Password", shaPass);

    SQLDatabase::execQuery(query);

    if (!query.first())
        throw DBErrors::GetValue("There is no such record");

    return query.value(0).toInt();
}


const qint64 SQLDatabase::getUserIdByUsername(const QString &username)
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


const qint64 SQLDatabase::getUserIdByAccessToken(const QString &accessToken)
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


const QString SQLDatabase::generateAccessToken(const qint64 userId)
{
    SQLDatabase::validateIsOpen();

    Security security("keys/server");
    auto accessTokenSTD = security.SHA256generatorRandom();
    QString accessTokenQT = QString::fromUtf8(accessTokenSTD.c_str());
    auto key = base64_encode(security.encryptPrivateMSG(accessTokenSTD));

    QSqlQuery query(SQLDatabase::db);
    query.prepare("INSERT INTO AccessTokens (AccessToken, UserID) "
                  "VALUES (:AccessToken, :UserID)");
    query.bindValue(":AccessToken", accessTokenQT);
    query.bindValue(":UserID", userId);

    SQLDatabase::execQuery(query);
    return QString::fromUtf8(key.c_str());
}


const QString SQLDatabase::getUserAccessToken(const qint64 userId)
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


const DBModelUser SQLDatabase::getUserInfo(const qint64 &userId)
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


const DBModelChat SQLDatabase::getChatInfo(const qint64 &chatId)
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


const DBModelMessage SQLDatabase::getMessageInfo(const qint64 &messageId)
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


const DBMessageList SQLDatabase::getUpdates(const qint64 &userId, const qint64 &lastMessageId)
{
    DBMessageList messageList;
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("SELECT m.ID, m.SenderID, m.ChatID, m.MsgText, m.Created, u.Username FROM Messages m "
                  "JOIN Users u ON u.ID = m.SenderID "
                  "WHERE m.ID > :LastMessageID AND "
                  "m.ChatID IN (SELECT m.ChatID FROM Members m WHERE m.MemberID = :UserID) AND "
                  "m.SenderID != :UserID "
                  "ORDER BY m.Created");
    query.bindValue(":LastMessageID", lastMessageId);
    query.bindValue(":UserID", userId);

    SQLDatabase::execQuery(query);

    while (query.next())
    {
        DBModelMessage messageModel;

        messageModel.id = query.value(0).toInt();
        messageModel.senderId = query.value(1).toInt();
        messageModel.chatId = query.value(2).toInt();
        messageModel.msgText = query.value(3).toString();
        messageModel.createdAt = query.value(4).toString();
        messageModel.sendeUsername = query.value(5).toString();

        messageList.push_back(messageModel);
    }

    return messageList;
}


const DBMessageList SQLDatabase::getMessageList(const qint64 &chatId, const qint64 &offset)
{
    // TODO: in future use offset
    DBMessageList messageList;
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);
    query.prepare("SELECT m.ID, m.SenderID, m.ChatID, m.MsgText, m.Created, u.Username FROM Messages m "
                  "JOIN Users u ON u.ID = m.SenderID "
                  "WHERE m.ChatID = :ChatID "
                  "ORDER BY m.Created");
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
        messageModel.sendeUsername = query.value(5).toString();

        messageList.push_back(messageModel);
    }

    return messageList;
}


const DBChatList SQLDatabase::getChatList(const qint64 &userId, const qint64 &offset)
{
    // TODO: in future use offset
    DBChatList chatList;
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);
    query.prepare("SELECT * FROM Chats c WHERE c.ID IN (SELECT m.ChatID FROM Members m WHERE m.MemberID = :MemberID)");
    query.bindValue(":MemberID", userId);

    SQLDatabase::execQuery(query);

    while (query.next())
    {
        DBModelChat chatModel;

        chatModel.id = query.value(0).toInt();
        chatModel.creatorId = query.value(1).toInt();
        chatModel.chatName = query.value(2).toString();
        chatModel.createdAt = query.value(3).toString();

        chatList.push_back(chatModel);
    }

    return chatList;
}


const qint64 SQLDatabase::getChatId(const qint64 &userId, const QString &chatName)
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
