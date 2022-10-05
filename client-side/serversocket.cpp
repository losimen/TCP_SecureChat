#include "serversocket.h"


ServerSocket::ServerSocket(QObject *parent)
    : QObject{parent}
{
    connect(&_socket, SIGNAL(connected()), this, SLOT(do_connected()));
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(do_onReadyRead()));
}


void ServerSocket::connectToHost(const QString &IPv4, const qint16 &port)
{
    qDebug() << "connecting..";
    _socket.connectToHost(IPv4, port);
}


void ServerSocket::write(const QByteArray &buffer)
{
    if (isBusy)
        return;

    _socket.write(buffer);
    isBusy = true;
}


ServerSocket &ServerSocket::getInstance()
{
    static ServerSocket socket;
    return socket;
}


void ServerSocket::do_connected()
{
    qDebug() << "connected";
}


void ServerSocket::do_errorOccured()
{
    qDebug() << "error occured";
}


void ServerSocket::do_onReadyRead()
{
    isBusy = false;
    emit on_respond(_socket.readAll());
}
