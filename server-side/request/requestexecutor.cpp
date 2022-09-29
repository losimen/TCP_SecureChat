#include "requestexecutor.h"
#include "servertypes.h"
#include "clienttypes.h"
#include "statuscodes.h"


RequestExecutor::RequestExecutor()
{

}

ClientTypes::InvalidFormat RequestExecutor::invalidFormat(const QString what)
{
    ClientTypes::InvalidFormat invalidFormat_client;

    invalidFormat_client.parseData(StatusCodes::badRequest, what);

    return invalidFormat_client;
}


ClientTypes::MissingAgument RequestExecutor::missingArgument(const QString what)
{
    ClientTypes::MissingAgument missingArgument_client;

    missingArgument_client.parseData(StatusCodes::badRequest, what);

    return missingArgument_client;
}


ClientTypes::InternalError RequestExecutor::internalError(const QString what)
{
    ClientTypes::InternalError internalError_client;

    internalError_client.parseData(StatusCodes::badRequest, what);

    return internalError_client;
}


ClientTypes::LogIn RequestExecutor::logIn(const ServerTypes::LogIn &logIn_server)
{
    ClientTypes::LogIn logIn_client;
    // do request main job here

    logIn_client.parseData(StatusCodes::ok, logIn_server.username);

    return logIn_client;
}
