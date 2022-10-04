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
