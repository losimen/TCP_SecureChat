#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>

#include "requesthandler.h"


class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = nullptr);
    void setSocket(int descriptor);

public slots:
    void disconnected();
    void readyRead();
    void requestResult(QByteArray number, RequestHandler *handlerRequest);

private:
    QTcpSocket *socket;

    static const qint8 AMOUNT_OT_THREADS;
};

#endif // CLIENTSOCKET_H
