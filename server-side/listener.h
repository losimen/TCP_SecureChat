#pragma once

#include <QTcpServer>


class Listener : public QTcpServer
{
    Q_OBJECT;

public:
    explicit Listener(QObject *parent = 0);
    void startServer();

protected:
    void incomingConnection(qintptr handle);

};
