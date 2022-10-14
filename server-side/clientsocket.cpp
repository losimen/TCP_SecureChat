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
   qDebug() << "New connection" << socket->peerAddress().toString() + ":" + QString::number(socket->peerPort());
}


void ClientSocket::disconnected()
{
    qDebug() << "Diconnected" << socket->peerAddress().toString() + ":" + QString::number(socket->peerPort());
    socket->close();
}


void ClientSocket::readyRead()
{
    RequestHandler *requestHandler = new RequestHandler();
    requestHandler->setAutoDelete(false);
    requestHandler->setBuffer(socket->readAll());

    connect(requestHandler, SIGNAL(on_finishRequest(QByteArray,RequestHandler*)), SLOT(requestResult(QByteArray,RequestHandler*)), Qt::QueuedConnection);

    QThreadPool::globalInstance()->start(requestHandler);
}


void ClientSocket::requestResult(QByteArray toSend, RequestHandler *handlerRequest)
{
    socket->write(toSend);
    delete handlerRequest;
}

