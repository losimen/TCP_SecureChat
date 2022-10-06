#include "requesthandler.h"
#include "requestexecutor.h"
#include "requestvalidator.h"
#include "requestmethods.h"
#include "servertypes.h"
#include "servererrors.h"
#include "statuscodes.h"
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
        else if (REQUEST_METHOD == RequestMethods::createChat)
        {
            const ServerTypes::CreateChat createChat_server = RequestValidator::createChat(db, jsonObject);
            const ClientTypes::CreateChat createChat_client = RequestExecutor::createChat(db, createChat_server);

            answer = createChat_client.serializeData();
        }
        else if (REQUEST_METHOD == RequestMethods::addMember)
        {
            const ServerTypes::AddMember addMember_server = RequestValidator::addMember(db, jsonObject);
            const ClientTypes::AddMember addMember_client = RequestExecutor::addMember(db, addMember_server);

            answer = addMember_client.serializeData();
        }
        else if (REQUEST_METHOD == RequestMethods::sendMessage)
        {
            const ServerTypes::SendMessage sendMessage_server = RequestValidator::sendMessage(db, jsonObject);
            const ClientTypes::SendMessage sendMessage_client = RequestExecutor::sendMessage(db, sendMessage_server);

            answer = sendMessage_client.serializeData();
        }
        else if (REQUEST_METHOD == RequestMethods::getMessageList)
        {
            const ServerTypes::GetMessageList getMessageList_server = RequestValidator::getMessageList(db, jsonObject);
            const ClientTypes::GetMessageList getMessageList_client = RequestExecutor::getMessageList(db, getMessageList_server);

            answer = getMessageList_client.serializeData();
        }
        else if (REQUEST_METHOD == RequestMethods::getChatList)
        {
            const ServerTypes::GetChatList getChatList_server = RequestValidator::getChatList(db, jsonObject);
            const ClientTypes::GetChatList getChatList_client = RequestExecutor::getChatList(db, getChatList_server);

            answer = getChatList_client.serializeData();
        }
        else if (REQUEST_METHOD == RequestMethods::getUpdates)
        {
            const ServerTypes::GetUpdates getUpdates_server = RequestValidator::getUpdates(db, jsonObject);
            const ClientTypes::GetUpdates getUpdates_client = RequestExecutor::getUpdates(db, getUpdates_server);

            answer = getUpdates_client.serializeData();
        }
        else
        {
            throw ServerErrors::NotFound("There is no such method");
        }

    }
    catch (ServerErrors::MyServerException &err)
    {
        const ClientTypes::Error error = RequestExecutor::error(err.getStatusCode(), err.what());
        answer = error.serializeData();
    }
    catch (...)
    {
        const ClientTypes::Error invalidFormat_client = RequestExecutor::error(StatusCodes::internalError ,"Internal error");
        answer = invalidFormat_client.serializeData();
    }

    emit on_finishRequest(answer, this);
}
