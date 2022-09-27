#include "clientsocket.h"

const qint8 ClientSocket::AMOUNT_OT_THREADS = 3;

ClientSocket::ClientSocket(QObject *parent)
    : QObject{parent}
{
    QThreadPool::globalInstance()->setMaxThreadCount(AMOUNT_OT_THREADS);
}

void ClientSocket::setSocket(int descriptor)
{
   socket = new QTcpSocket(this);

   connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
   connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

   socket->setSocketDescriptor(descriptor);

   qDebug() << "Created socket";
}


void ClientSocket::disconnected()
{
    socket->close();
}

void ClientSocket::readyRead()
{
    HandlerRequest *handlerRequest = new HandlerRequest();
    handlerRequest->setAutoDelete(false);
    handlerRequest->setBuffer(socket->readAll());

    connect(handlerRequest, SIGNAL(on_finishRequest(int,HandlerRequest*)), SLOT(requestResult(int,HandlerRequest*)), Qt::QueuedConnection);

    QThreadPool::globalInstance()->start(handlerRequest);
}

void ClientSocket::requestResult(int number, HandlerRequest *handlerRequest)
{
    QByteArray buffer;

    buffer.append("\r\nHey I am answer ");
    buffer.append(QString::number(number).toUtf8());
    socket->write(buffer);

    delete handlerRequest;
}
