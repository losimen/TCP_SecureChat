#include "handlerrequest.h"

HandlerRequest::HandlerRequest()
{

}

void HandlerRequest::setBuffer(QByteArray buffer)
{
    HandlerRequest::buffer = buffer;
}

void HandlerRequest::run()
{
    // Do request job here...    
    QJsonDocument itemDoc = QJsonDocument::fromJson(HandlerRequest::buffer);
    qDebug() << "utf-8 " << QString(HandlerRequest::buffer).toUtf8();
    QJsonObject rootObject = itemDoc.object();

    qDebug() << HandlerRequest::buffer;
    qDebug() << rootObject.length();

    emit on_finishRequest(34, this);
}
