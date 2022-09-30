#include "requesthandler.h"
#include "requestexecutor.h"
#include "requestvalidator.h"
#include "requestmethods.h"
#include "servertypes.h"
#include "servererrors.h"
#include "statuscodes.h"


RequestHandler::RequestHandler()
{

}

void RequestHandler::setBuffer(QByteArray buffer)
{
    RequestHandler::buffer = buffer;
}

void RequestHandler::run()
{
    QByteArray answer;

    try
    {
        QJsonObject jsonObject = RequestValidator::format(RequestHandler::buffer);
        const QString REQUEST_METHOD = jsonObject["method"].toString();

        if (REQUEST_METHOD == RequestMethods::logIn)
        {
            const ServerTypes::LogIn logIn_server = RequestValidator::logIn(jsonObject);
            const ClientTypes::LogIn logIn_client = RequestExecutor::logIn(logIn_server);

            answer = logIn_client.serializeData();
        }
        else if (REQUEST_METHOD == RequestMethods::signUp)
        {
            const ServerTypes::SignUp signUp_server = RequestValidator::signUp(jsonObject);
            const ClientTypes::SignUp signUp_client = RequestExecutor::signUp(signUp_server);

            answer = signUp_client.serializeData();
        }
        else
        {
            throw ServerErrors::NotFound("There is no such method");
        }

    }
    catch (ServerErrors::InvalidFormat err)
    {
        const ClientTypes::Error invalidFormat_client = RequestExecutor::error(StatusCodes::badRequest, err.what());
        answer = invalidFormat_client.serializeData();
    }
    catch (ServerErrors::MissingArgument err)
    {
        const ClientTypes::Error invalidFormat_client = RequestExecutor::error(StatusCodes::badRequest, err.what());
        answer = invalidFormat_client.serializeData();
    }
    catch (ServerErrors::NotFound err)
    {
        const ClientTypes::Error invalidFormat_client = RequestExecutor::error(StatusCodes::notFound, err.what());
        answer = invalidFormat_client.serializeData();
    }
    catch (...)
    {
        const ClientTypes::Error invalidFormat_client = RequestExecutor::error(StatusCodes::internalError ,"Internal error");
        answer = invalidFormat_client.serializeData();
    }

    emit on_finishRequest(answer, this);
}
