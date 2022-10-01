#include "requestvalidator.h"
#include "servererrors.h"
#include "dberrors.h"


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

    try
    {
        createChat_server._creatorId = db.getUserIdByAccessToken(createChat_server.accessToken);
    }
    catch (DBErrors::GetValue &err)
    {
        throw ServerErrors::NotFound("Auth error");
    }

    return createChat_server;
}
