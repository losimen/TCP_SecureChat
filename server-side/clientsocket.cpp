#include "clientsocket.h"


ClientSocket::ClientSocket(QObject *parent)
    : QObject{parent}
{

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
}

void ClientSocket::requestResult(int number)
{

}
