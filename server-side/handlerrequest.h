#ifndef HANDLERREQUEST_H
#define HANDLERREQUEST_H

#include <QRunnable>
#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>


class HandlerRequest : public QObject, public QRunnable
{
    Q_OBJECT

public:
    HandlerRequest();
    void setBuffer(QByteArray buffer);

signals:
    void on_finishRequest(int number, HandlerRequest *handlerRequest);

protected:
    void run();

private:
    QByteArray buffer;
};

#endif // HANDLERREQUEST_H
