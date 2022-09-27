#ifndef HANDLERREQUEST_H
#define HANDLERREQUEST_H

#include <QRunnable>
#include <QObject>
#include <QDebug>


class HandlerRequest : public QObject, public QRunnable
{
    Q_OBJECT
public:
    HandlerRequest();

signals:
    void result(int number);

protected:
    void run();
};

#endif // HANDLERREQUEST_H
