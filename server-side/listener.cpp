#include "listener.h"


Listener::Listener(QObject *parent) :
    QTcpServer(parent)
{
    pool = new QThreadPool(this);
    pool->setMaxThreadCount(3);
}


void Listener::startServer()
{
    if (Listener::listen(QHostAddress::Any, 54000))
        qDebug() << "Server started";
    else
        qDebug() << "Server didn't start";
}

void Listener::incomingConnection(qintptr handle)
{
    qDebug() << "New connection";

    ClientSocket *client = new ClientSocket(this);
    client->setSocket(handle);

//    MyRunnable *task = new MyRunnable();
//    task->setAutoDelete(true);

//    task->socketDescriptor = handle;
//    pool->start(task);
}

void Listener::setSocket(int descriptor)
{

}
