#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>


class ServerSocket : public QObject
{
    Q_OBJECT

public:
    static ServerSocket &getInstance();
    void connectToHost(const QString &IPv4, const qint16 &port);
    void write(const QByteArray &buffer);

signals:
    void on_respond(QByteArray buffer);

private slots:
    void do_connected();
    void do_errorOccured();
    void do_onReadyRead();

private:
    QTcpSocket _socket;
    QString IPv4;
    qint16 port;

    bool isBusy;

    explicit ServerSocket(QObject *parent = nullptr);

};

#endif // SERVERSOCKET_H
