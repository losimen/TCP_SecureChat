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
    QJsonParseError *err = nullptr;
    QJsonDocument itemDoc = QJsonDocument::fromJson(RequestHandler::buffer, err);

    QJsonObject rootObject = itemDoc.object();

    qDebug() << RequestHandler::buffer;
    qDebug() << rootObject.length() << " " << rootObject["responce"].toDouble();

    emit on_finishRequest(34, this);
}
