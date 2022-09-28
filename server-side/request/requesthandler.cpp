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
    try {
        QJsonObject object = RequestValidator::format(RequestHandler::buffer);
        const QString REQUEST_METHOD = object["method"].toString();

        if (REQUEST_METHOD == RequestMethods::logIn)
        {
            ServerTypes::LogIn logIn_server = RequestValidator::logIn(object);
            RequestExecutor::logIn(logIn_server);
        }
        else if (REQUEST_METHOD == RequestMethods::signUp)
        {
            RequestValidator::signUp(object);
        }

    } catch (ServerErrors::InvalidFormat) {
        // build responce invalid format
        ;
    } catch (ServerErrors::MissingArgument) {
        // build responce missing argument
        ;
    } catch (...) {
        // build responce internal error
        ;
    }


    emit on_finishRequest(34, this);
}
