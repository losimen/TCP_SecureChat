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
