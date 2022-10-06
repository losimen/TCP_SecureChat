#include "backgroundworker.h"
#include "serversocket.h"
#include "statuscodes.h"
#include "servertypes.h"
#include "cacheemulator.h"
#include "serversocket.h"


qint8 const BackGroundWorker::maxThreadCount = 3;


BackGroundWorker &BackGroundWorker::getInstance()
{
    static BackGroundWorker object;
    return object;
}


void BackGroundWorker::run()
{
    ServerTypes::GetUpdates data;

    qDebug() << "her";
    connect(this, SIGNAL(Write(QByteArray)), &ServerSocket::getInstance(), SLOT(write(QByteArray)));
    connect(&ServerSocket::getInstance(), SIGNAL(on_respond(QByteArray)), this, SLOT(do_parseResponce(QByteArray)));
    data.offset = 0;

    while(true)
    {
        if (CacheEmulator::getInstance().getLastMessageId() == 0)
        {
            QThread::msleep(1500);
            continue;
        }

        data.accessToken = CacheEmulator::getInstance().getAccessToken();
        data.lastMessageId = CacheEmulator::getInstance().getLastMessageId();

        emit Write(data.serializeData());

        QThread::msleep(1500);
    }
}


void BackGroundWorker::do_parseResponce(QByteArray buffer)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(buffer);
    QJsonObject jsonObject = jsonDocument.object();

    const qint16 statusCode = jsonObject["statusCode"].toInt();

    // TODO: show error in UI
    if (statusCode != StatusCodes::ok)
        return;

    if (jsonObject.find("isUpdate") != jsonObject.constEnd())
         return;

    auto arr = jsonObject["messageList"].toArray();

    if (arr.isEmpty())
        return;

    std::unique_ptr<DBMessageList> msgList;
    msgList.reset(new DBMessageList());

    for (auto el: arr)
    {
        DBModelMessage message;

        message.id = el.toObject()["id"].toInt();
        message.msgText = el.toObject()["msgText"].toString();
        message.sendeUsername = el.toObject()["senderUsername"].toString();
        message.createdAt = el.toObject()["createdAt"].toString();
        message.chatId = el.toObject()["chatId"].toInteger();

        msgList->push_back(message);
    }

    emit on_newMessages(msgList);
}


BackGroundWorker::BackGroundWorker()
{
    QThreadPool::globalInstance()->setMaxThreadCount(maxThreadCount);
}
