#ifndef LISTENER_H
#define LISTENER_H

#include <QTcpServer>
#include <QObject>
#include <QThreadPool>


class Listener : public QTcpServer
{
    Q_OBJECT;

public:
    explicit Listener(QObject *parent = 0);
    void startServer();

protected:
    void incomingConnection(qintptr handle);

};

#endif // LISTENER_H
