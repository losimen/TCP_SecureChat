#include "requestexecutor.h"
#include "servertypes.h"
#include "clienttypes.h"
#include "statuscodes.h"


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
    // do request main job here

    logIn_client.parseData(StatusCodes::ok, logIn_server.username);

    return logIn_client;
}
