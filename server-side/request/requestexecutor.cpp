#include "requestexecutor.h"
#include "servertypes.h"
#include "clienttypes.h"
#include "statuscodes.h"
#include "sqldatabase.h"


RequestExecutor::RequestExecutor()
{

}


ClientTypes::Error RequestExecutor::error(const StatusCodes &statusCode, const QString &what)
{
    ClientTypes::Error invalidFormat_client;

    invalidFormat_client.parseData(statusCode, what);

    return invalidFormat_client;
}


ClientTypes::LogIn RequestExecutor::logIn(const ServerTypes::LogIn &logIn_server)
{
    ClientTypes::LogIn logIn_client;

    logIn_client.parseData(StatusCodes::ok, logIn_server.username);

    return logIn_client;
}


ClientTypes::SignUp RequestExecutor::signUp(const ServerTypes::SignUp &signUp_server)
{
    QString accessToken;
    ClientTypes::SignUp signUp_client;
    SQLDatabase db;
    qint64 userId;

    userId = db.saveUser(signUp_server.username, signUp_server.password);
    accessToken = db.generateAccessToken(userId);

    signUp_client.parseData(StatusCodes::ok, accessToken);

    return signUp_client;
}
