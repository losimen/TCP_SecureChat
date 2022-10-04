#include "inputvalidator.h"
#include "clienterrors.h"

InputValidator::InputValidator()
{

}


ServerTypes::LogIn InputValidator::logIn(const QString &username, const QString &password)
{
    ServerTypes::LogIn logIn_server;

    if (username.length() == 0 || username.length() < 3)
        throw ClientErrors::InvalidInput("Username has to be at least 3 characters");

    if (password.length() == 0 || password.length() < 8)
        throw ClientErrors::InvalidInput("Password has to be at least 8 characters");

    if (username.length() > 15)
        throw ClientErrors::InvalidInput("To long username");

    if (password.length() > 256)
        throw ClientErrors::InvalidInput("To long password");

    logIn_server.username = username;
    logIn_server.password = password;

    return logIn_server;
}


ServerTypes::SignUp InputValidator::signUp(const QString &username, const QString &password_1, const QString &password_2)
{
    ServerTypes::SignUp signUp_server;


    if (username.length() == 0 || username.length() < 3)
        throw ClientErrors::InvalidInput("Username has to be at least 3 characters");

    if (password_1.length() == 0 || password_1.length() < 8 ||
        password_2.length() == 0 || password_2.length() < 8)
        throw ClientErrors::InvalidInput("Password has to be at least 8 characters");

    if (password_1 != password_2)
        throw ClientErrors::InvalidInput("Passwords aren't equal");

    if (username.length() > 15)
        throw ClientErrors::InvalidInput("To long username");

    if (password_1.length() > 256)
        throw ClientErrors::InvalidInput("To long password");

    signUp_server.username = username;
    signUp_server.password = password_1;

    return signUp_server;
}
