#include "requestvalidator.h"
#include "servererrors.h"
#include "dberrors.h"


qint64 RequestValidator::validateAccessToken(SQLDatabase &db, const QString &accessToken)
{
    qint64 userId;

    try
    {
        userId = db.getUserIdByAccessToken(accessToken);
    }
    catch (DBErrors::GetValue &err)
    {
        throw ServerErrors::Unauthorized("Auth error");
    }

    return userId;
}


qint64 RequestValidator::validateUsername(SQLDatabase &db, const QString &username)
{
    qint64 userId;

    try
    {
        userId = db.getUserIdByUsername(username);
    }
    catch (DBErrors::GetValue &err)
    {
        throw ServerErrors::NotFound("User with such username doesn't exist");
    }

    return userId;
}


qint64 RequestValidator::validateChatName(SQLDatabase &db, const qint64 userId, const QString &chatName)
{
    qint64 chatId;

    try
    {
        chatId = db.getChatId(userId, chatName);
    }
    catch (DBErrors::GetValue &err)
    {
        throw ServerErrors::NotFound("Chat doesn't exist");
    }

    return chatId;
}


DBModelUser RequestValidator::validateUserId(SQLDatabase &db, const qint64 userId)
{
    DBModelUser userModel;

    try
    {
        userModel = db.getUserInfo(userId);
    }
    catch (DBErrors::GetValue &err)
    {
        throw ServerErrors::NotFound("There is no such user id");
    }

    return userModel;
}


DBModelChat RequestValidator::validateChatId(SQLDatabase &db, const qint64 chatId)
{
    DBModelChat chatModel;

    try
    {
        chatModel = db.getChatInfo(chatId);
    }
    catch (DBErrors::GetValue &err)
    {
        throw ServerErrors::NotFound("There is no such chat id");
    }

    return chatModel;
}


DBModelMessage RequestValidator::validateMessageId(SQLDatabase &db, const qint64 messageId)
{
    DBModelMessage messageModel;

    try
    {
        messageModel = db.getMessageInfo(messageId);
    }
    catch (DBErrors::GetValue &err)
    {
        throw ServerErrors::NotFound("There is no such message id");
    }

    return messageModel;
}


RequestValidator::RequestValidator()
{

}


QJsonObject RequestValidator::format(const QByteArray &buffer)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(buffer);
    QJsonObject jsonObject = jsonDocument.object();

    if (jsonObject.isEmpty())
        throw ServerErrors::InvalidFormat("Inavlid request format");

    if (jsonObject.find("method") == jsonObject.constEnd())
        throw ServerErrors::InvalidFormat("Not found request method");

    return jsonObject;
}


ServerTypes::LogIn RequestValidator::logIn(SQLDatabase &db, const QJsonObject &buffer)
{
    ServerTypes::LogIn logIn_server;

    if (buffer.find("username") == buffer.constEnd())
        throw ServerErrors::MissingArgument("username");

    if (buffer.find("password") == buffer.constEnd())
        throw ServerErrors::MissingArgument("password");

    logIn_server.username = buffer["username"].toString();
    logIn_server.password = buffer["password"].toString();

    try
    {
        logIn_server._userId = db.getUserIdByAuth(logIn_server.username, logIn_server.password);
    }
    catch (DBErrors::GetValue &err)
    {
        throw ServerErrors::NotFound("Invalid login or password");
    }

    return logIn_server;
}


ServerTypes::SignUp RequestValidator::signUp(SQLDatabase &db, const QJsonObject &buffer)
{
    ServerTypes::SignUp signUp_server;

    if (buffer.find("username") == buffer.constEnd())
        throw ServerErrors::MissingArgument("username");

    if (buffer.find("password") == buffer.constEnd())
        throw ServerErrors::MissingArgument("password");

    signUp_server.username = buffer["username"].toString();
    signUp_server.password = buffer["password"].toString();

    try
    {
        db.getUserIdByUsername(signUp_server.username);
    }
    catch (DBErrors::GetValue &err)
    {
        return signUp_server;
    }

    throw ServerErrors::Conflict("User already exists with such username");
}


ServerTypes::CreateChat RequestValidator::createChat(SQLDatabase &db, const QJsonObject &buffer)
{
    ServerTypes::CreateChat createChat_server;

    if (buffer.find("accessToken") == buffer.constEnd())
        throw ServerErrors::MissingArgument("accessToken");

    if (buffer.find("chatName") == buffer.constEnd())
        throw ServerErrors::MissingArgument("chatName");

    createChat_server.accessToken = buffer["accessToken"].toString();
    createChat_server.chatName = buffer["chatName"].toString();

    createChat_server._creatorId = RequestValidator::validateAccessToken(db, createChat_server.accessToken);

    return createChat_server;
}


ServerTypes::AddMember RequestValidator::addMember(SQLDatabase &db, const QJsonObject &buffer)
{
    ServerTypes::AddMember addMember_server;

    if (buffer.find("accessToken") == buffer.constEnd())
        throw ServerErrors::MissingArgument("accessToken");

    if (buffer.find("username") == buffer.constEnd())
        throw ServerErrors::MissingArgument("username");

    if (buffer.find("chatName") == buffer.constEnd())
        throw ServerErrors::MissingArgument("chatName");

    addMember_server.accessToken = buffer["accessToken"].toString();
    addMember_server.memberToAddUsername = buffer["username"].toString();
    addMember_server.chatName = buffer["chatName"].toString();

    qint64 creatorId = RequestValidator::validateAccessToken(db, addMember_server.accessToken);

    addMember_server._userIdToAdd = RequestValidator::validateUsername(db, addMember_server.memberToAddUsername);
    addMember_server._chatId = RequestValidator::validateChatName(db, creatorId, addMember_server.chatName);

    return addMember_server;
}


ServerTypes::SendMessage RequestValidator::sendMessage(SQLDatabase &db, const QJsonObject &buffer)
{
    ServerTypes::SendMessage sendMessage_server;

    if (buffer.find("accessToken") == buffer.constEnd())
        throw ServerErrors::MissingArgument("accessToken");

    if (buffer.find("msgText") == buffer.constEnd())
        throw ServerErrors::MissingArgument("msgText");

    if (buffer.find("chatId") == buffer.constEnd())
        throw ServerErrors::MissingArgument("chatId");

    sendMessage_server.accessToken = buffer["accessToken"].toString();
    sendMessage_server.msgText = buffer["msgText"].toString();
    sendMessage_server.chatId = buffer["chatId"].toInt();

    RequestValidator::validateChatId(db, sendMessage_server.chatId);
    sendMessage_server._senderId = RequestValidator::validateAccessToken(db, sendMessage_server.accessToken);

    return sendMessage_server;
}


ServerTypes::GetMessageList RequestValidator::getMessageList(SQLDatabase &db, const QJsonObject &buffer)
{
    ServerTypes::GetMessageList getMessageList_server;

    if (buffer.find("accessToken") == buffer.constEnd())
        throw ServerErrors::MissingArgument("accessToken");

    if (buffer.find("chatId") == buffer.constEnd())
        throw ServerErrors::MissingArgument("chatId");

    if (buffer.find("offset") == buffer.constEnd())
        throw ServerErrors::MissingArgument("offset");

    getMessageList_server.accessToken = buffer["accessToken"].toString();
    getMessageList_server.chatId = buffer["chatId"].toInt();
    getMessageList_server.offset = buffer["offset"].toInt();

    RequestValidator::validateAccessToken(db, getMessageList_server.accessToken);
    RequestValidator::validateChatId(db, getMessageList_server.chatId);

    return getMessageList_server;
}

ServerTypes::GetChatList RequestValidator::getChatList(SQLDatabase &db, const QJsonObject &buffer)
{
    ServerTypes::GetChatList getChatList_server;

    if (buffer.find("accessToken") == buffer.constEnd())
        throw ServerErrors::MissingArgument("accessToken");

    if (buffer.find("offset") == buffer.constEnd())
        throw ServerErrors::MissingArgument("offset");

    getChatList_server.accessToken = buffer["accessToken"].toString();
    getChatList_server.offset = buffer["offset"].toInteger();

    getChatList_server._userId = RequestValidator::validateAccessToken(db, getChatList_server.accessToken);

    return getChatList_server;
}


ServerTypes::GetUpdates RequestValidator::getUpdates(SQLDatabase &db, const QJsonObject &buffer)
{
    ServerTypes::GetUpdates getUpdates_server;

    if (buffer.find("accessToken") == buffer.constEnd())
        throw ServerErrors::MissingArgument("accessToken");

    if (buffer.find("lastMessageId") == buffer.constEnd())
        throw ServerErrors::MissingArgument("lastMessageId");

    if (buffer.find("offset") == buffer.constEnd())
        throw ServerErrors::MissingArgument("offset");

    getUpdates_server.accessToken = buffer["accessToken"].toString();
    getUpdates_server.offset = buffer["offset"].toInteger();
    getUpdates_server.lastMessageId = buffer["lastMessageId"].toInteger();
    getUpdates_server._userId = RequestValidator::validateAccessToken(db, getUpdates_server.accessToken);

    return getUpdates_server;
}


ServerTypes::GetPubKey RequestValidator::getPubKey(SQLDatabase &db, const QJsonObject &buffer)
{
    ServerTypes::GetPubKey getPubKey_server;

    return getPubKey_server;
}
