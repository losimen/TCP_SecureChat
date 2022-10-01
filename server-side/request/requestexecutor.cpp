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

    invalidFormat_client.statusCode = statusCode;
    invalidFormat_client.what = what;

    return invalidFormat_client;
}


ClientTypes::LogIn RequestExecutor::logIn(SQLDatabase &db, const ServerTypes::LogIn &logIn_server)
{
    ClientTypes::LogIn logIn_client;
    QString accessToken;

    accessToken = db.getUserAccessToken(logIn_server._userId);

    logIn_client.statusCode = StatusCodes::ok;
    logIn_client.accessToken = accessToken;

    return logIn_client;
}


ClientTypes::SignUp RequestExecutor::signUp(SQLDatabase &db, const ServerTypes::SignUp &signUp_server)
{
    QString accessToken;
    ClientTypes::SignUp signUp_client;
    qint64 userId;

    userId = db.saveUser(signUp_server.username, signUp_server.password);
    accessToken = db.generateAccessToken(userId);

    signUp_client.statusCode = StatusCodes::ok;
    signUp_client.accessToken = accessToken;

    return signUp_client;
}
