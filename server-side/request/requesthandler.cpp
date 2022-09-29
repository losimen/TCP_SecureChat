#include "requesthandler.h"
#include "requestexecutor.h"
#include "requestvalidator.h"
#include "requestmethods.h"
#include "servertypes.h"
#include "servererrors.h"


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

    try {
        QJsonObject object = RequestValidator::format(RequestHandler::buffer);
        const QString REQUEST_METHOD = object["method"].toString();

        if (REQUEST_METHOD == RequestMethods::logIn)
        {
            const ServerTypes::LogIn logIn_server = RequestValidator::logIn(object);
            const ClientTypes::LogIn logIn_client = RequestExecutor::logIn(logIn_server);

            answer = logIn_client.serializeData();
        }
        else if (REQUEST_METHOD == RequestMethods::signUp)
        {
            RequestValidator::signUp(object);
        }
        else
        {
            // build responce notfound
        }

    } catch (ServerErrors::InvalidFormat err) {
        const ClientTypes::InvalidFormat invalidFormat_client = RequestExecutor::invalidFormat(err.what());

        answer = invalidFormat_client.serializeData();
    } catch (ServerErrors::MissingArgument err) {
        const ClientTypes::InvalidFormat invalidFormat_client = RequestExecutor::invalidFormat(err.what());

        answer = invalidFormat_client.serializeData();
    } catch (...) {
        const ClientTypes::InvalidFormat invalidFormat_client = RequestExecutor::invalidFormat("Internal error");

        answer = invalidFormat_client.serializeData();
    }


    emit on_finishRequest(answer, this);
}
