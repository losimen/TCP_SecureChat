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
        db.getUserIdByAuth(logIn_server.username, logIn_server.password);
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
