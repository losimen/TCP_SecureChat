#include "requesthandler.h"
#include "requestexecutor.h"
#include "requestvalidator.h"
#include "requestmethods.h"
#include "servertypes.h"
#include "servererrors.h"
#include "statuscodes.h"
#include "dberrors.h"
#include "sqldatabase.h"


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
        SQLDatabase db;
        QJsonObject jsonObject = RequestValidator::format(RequestHandler::buffer);
        const QString REQUEST_METHOD = jsonObject["method"].toString();

        if (REQUEST_METHOD == RequestMethods::logIn)
        {
            const ServerTypes::LogIn logIn_server = RequestValidator::logIn(db, jsonObject);
            const ClientTypes::LogIn logIn_client = RequestExecutor::logIn(db, logIn_server);

            answer = logIn_client.serializeData();
        }
        else if (REQUEST_METHOD == RequestMethods::signUp)
        {
            const ServerTypes::SignUp signUp_server = RequestValidator::signUp(db, jsonObject);
            const ClientTypes::SignUp signUp_client = RequestExecutor::signUp(db, signUp_server);

            answer = signUp_client.serializeData();
        }
        else if (REQUEST_METHOD == RequestMethods::signUp)
        {
            const ServerTypes::SignUp signUp_server = RequestValidator::signUp(db, jsonObject);
            const ClientTypes::SignUp signUp_client = RequestExecutor::signUp(db, signUp_server);

            answer = signUp_client.serializeData();
        }
        else
        {
            throw ServerErrors::NotFound("There is no such method");
        }

    }
    catch (ServerErrors::InvalidFormat &err)
    {
        const ClientTypes::Error invalidFormat_client = RequestExecutor::error(StatusCodes::badRequest, err.what());
        answer = invalidFormat_client.serializeData();
    }
    catch (ServerErrors::MissingArgument &err)
    {
        const ClientTypes::Error missingArgument_client = RequestExecutor::error(StatusCodes::badRequest, err.what());
        answer = missingArgument_client.serializeData();
    }
    catch (ServerErrors::NotFound &err)
    {
        const ClientTypes::Error notFound_client = RequestExecutor::error(StatusCodes::notFound, err.what());
        answer = notFound_client.serializeData();
    }
    catch (ServerErrors::Conflict &err)
    {
        const ClientTypes::Error conflict = RequestExecutor::error(StatusCodes::conflict, err.what());
        answer = conflict.serializeData();
    }
    catch (DBErrors::Open &err)
    {
        const ClientTypes::Error open_client = RequestExecutor::error(StatusCodes::serviceUnavalibale, err.what());
        answer = open_client.serializeData();
    }
    catch (DBErrors::Exec &err)
    {
        const ClientTypes::Error open_client = RequestExecutor::error(StatusCodes::serviceUnavalibale, err.what());
        answer = open_client.serializeData();
    }
    catch (...)
    {
        const ClientTypes::Error invalidFormat_client = RequestExecutor::error(StatusCodes::internalError ,"Internal error");
        answer = invalidFormat_client.serializeData();
    }

    emit on_finishRequest(answer, this);
}
