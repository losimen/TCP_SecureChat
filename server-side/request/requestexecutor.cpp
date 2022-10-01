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
    ClientTypes::SignUp signUp_client;
    QString accessToken;
    qint64 userId;

    userId = db.insertUser(signUp_server.username, signUp_server.password);
    accessToken = db.generateAccessToken(userId);

    signUp_client.statusCode = StatusCodes::ok;
    signUp_client.accessToken = accessToken;

    return signUp_client;
}


ClientTypes::CreateChat RequestExecutor::createChat(SQLDatabase &db, const ServerTypes::CreateChat &createChat_server)
{
    ClientTypes::CreateChat createChat_client;

    createChat_client.statusCode = StatusCodes::ok;
    createChat_client.chatId = db.insertChat(createChat_server._creatorId, createChat_server.chatName);

    return createChat_client;
}


ClientTypes::AddMember RequestExecutor::addMember(SQLDatabase &db, const ServerTypes::AddMember &addMember_server)
{
    ClientTypes::AddMember addMember_client;

    db.insertMember(addMember_server._chatId, addMember_server._userIdToAdd);
    addMember_client.statusCode = StatusCodes::ok;

    return addMember_client;
}
