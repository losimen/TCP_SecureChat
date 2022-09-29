#ifndef HANDLERREQUEST_H
#define HANDLERREQUEST_H

#include <QRunnable>
#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>


class RequestHandler : public QObject, public QRunnable
{
    Q_OBJECT

public:
    RequestHandler();
    void setBuffer(QByteArray buffer);

signals:
    void on_finishRequest(QByteArray number, RequestHandler *handlerRequest);

protected:
    void run();

private:
    QByteArray buffer;
};

#endif // HANDLERREQUEST_H
