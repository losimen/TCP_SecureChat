#include "clientsocket.h"


ClientSocket::ClientSocket(QObject *parent)
    : QObject{parent}
{
    QThreadPool::globalInstance()->setMaxThreadCount(3);
}

void ClientSocket::setSocket(int descriptor)
{
   socket = new QTcpSocket(this);

   connect(socket, SIGNAL(connected()), this, SLOT(connected()));
   connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
   connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

   socket->setSocketDescriptor(descriptor);

   qDebug() << "Created socket";
}

void ClientSocket::connected()
{
    qDebug() << "event connected";
}

void ClientSocket::disconnected()
{
    qDebug() << "event disconnected";
    socket->close();
}

void ClientSocket::readyRead()
{
    qDebug() << "event ready read";
    qDebug() << socket->readAll();

    HandlerRequest *handlerRequest = new HandlerRequest();
    handlerRequest->setAutoDelete(true);
    connect(handlerRequest, SIGNAL(result(int)), this, SLOT(requestResult(int)), Qt::QueuedConnection);

    QThreadPool::globalInstance()->start(handlerRequest);
}

void ClientSocket::requestResult(int number)
{
    QByteArray buffer;
    buffer.append("\r\nHey I am answer ");
    buffer.append(QString::number(number).toUtf8());

    socket->write(buffer);
}
