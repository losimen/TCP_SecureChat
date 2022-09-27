#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>


class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = nullptr);
    void setSocket(int descriptor);
signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void requestResult(int number);

private:
    QTcpSocket *socket;
};

#endif // CLIENTSOCKET_H
