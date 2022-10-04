#include "listener.h"
#include "clientsocket.h"


Listener::Listener(QObject *parent) :
    QTcpServer(parent)
{

}


void Listener::startServer()
{
    if (Listener::listen(QHostAddress::LocalHost, 54000))
        qDebug() << "Server started";
    else
        qDebug() << "Server didn't start";
}


void Listener::incomingConnection(qintptr handle)
{
    ClientSocket *client = new ClientSocket(this);
    client->setSocket(handle);
}
