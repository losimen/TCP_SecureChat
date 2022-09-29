#include "requestvalidator.h"
#include "servererrors.h"


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


ServerTypes::LogIn RequestValidator::logIn(const QJsonObject &buffer)
{
    ServerTypes::LogIn logIn_data;

    if (buffer.find("username") == buffer.constEnd())
        throw ServerErrors::MissingArgument("username");

    if (buffer.find("password") == buffer.constEnd())
        throw ServerErrors::MissingArgument("password");

    logIn_data.parseData(buffer["username"].toString(),buffer["password"].toString());

    return logIn_data;
}


ServerTypes::SignUp RequestValidator::signUp(const QJsonObject &buffer)
{
    ServerTypes::SignUp signUp_data;

    if (buffer.find("username") == buffer.constEnd())
        throw ServerErrors::MissingArgument("username");

    if (buffer.find("password") == buffer.constEnd())
        throw ServerErrors::MissingArgument("password");

    signUp_data.parseData(buffer["username"].toString(),buffer["password"].toString());

    return signUp_data;
}
