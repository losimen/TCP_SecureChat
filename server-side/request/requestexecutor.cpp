#include "requestexecutor.h"
#include "servertypes.h"
#include "clienttypes.h"
#include "statuscodes.h"
#include "sqldatabase.h"
#include "security.h"
#include "base64.h"


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
    db.insertMember(createChat_client.chatId, createChat_server._creatorId);

    return createChat_client;
}


ClientTypes::AddMember RequestExecutor::addMember(SQLDatabase &db, const ServerTypes::AddMember &addMember_server)
{
    ClientTypes::AddMember addMember_client;

    db.insertMember(addMember_server._chatId, addMember_server._userIdToAdd);

    addMember_client.statusCode = StatusCodes::ok;

    return addMember_client;
}


ClientTypes::SendMessage RequestExecutor::sendMessage(SQLDatabase &db, const ServerTypes::SendMessage &sendMessage_server)
{
    ClientTypes::SendMessage sendMessage_client;

    db.insertMessage(sendMessage_server.chatId, sendMessage_server._senderId, sendMessage_server.msgText);

    sendMessage_client.statusCode = StatusCodes::ok;

    return sendMessage_client;
}


ClientTypes::GetMessageList RequestExecutor::getMessageList(SQLDatabase &db, const ServerTypes::GetMessageList &getMessageList_server)
{
    ClientTypes::GetMessageList getMessageList_client;

    getMessageList_client.statusCode = StatusCodes::ok;
    getMessageList_client.messageList = db.getMessageList(getMessageList_server.chatId, getMessageList_server.offset);

    return getMessageList_client;
}


ClientTypes::GetChatList RequestExecutor::getChatList(SQLDatabase &db, const ServerTypes::GetChatList &getChatList_server)
{
    ClientTypes::GetChatList getChatList_client;

    getChatList_client.statusCode = StatusCodes::ok;
    getChatList_client.chatList = db.getChatList(getChatList_server._userId, getChatList_server.offset);

    return getChatList_client;
}


ClientTypes::GetUpdates RequestExecutor::getUpdates(SQLDatabase &db, const ServerTypes::GetUpdates &getUpdates_server)
{
    ClientTypes::GetUpdates getUpdates_client;

    getUpdates_client.statusCode = StatusCodes::ok;
    getUpdates_client.messageList = db.getUpdates(getUpdates_server._userId, getUpdates_server.lastMessageId);

    return getUpdates_client;
}


ClientTypes::GetPubKey RequestExecutor::getPubKey(SQLDatabase &db, const ServerTypes::GetPubKey &getPubKey_server)
{
    Security security("keys/server");
    ClientTypes::GetPubKey getPubKey_client;

    getPubKey_client.statusCode = StatusCodes::ok;
    getPubKey_client.pubKey = security.getPubKey();

    return getPubKey_client;
}
