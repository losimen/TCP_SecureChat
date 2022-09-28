#include "requesthandler.h"

RequestHandler::RequestHandler()
{

}

void RequestHandler::setBuffer(QByteArray buffer)
{
    RequestHandler::buffer = buffer;
}

void RequestHandler::run()
{
    // Do request job here...    
    QJsonDocument itemDoc = QJsonDocument::fromJson(RequestHandler::buffer);
    qDebug() << "utf-8 " << QString(RequestHandler::buffer).toUtf8();
    QJsonObject rootObject = itemDoc.object();

    qDebug() << RequestHandler::buffer;
    qDebug() << rootObject.length();

    emit on_finishRequest(34, this);
}
