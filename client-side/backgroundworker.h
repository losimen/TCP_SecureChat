#pragma once

#include <QtGlobal>
#include <QObject>
#include <QThreadPool>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "dbmodelmessage.h"


class BackGroundWorker: public QObject, public QRunnable
{
    Q_OBJECT

public:
    static BackGroundWorker &getInstance();

    void startBackGroundTask();

protected:
    void run();

signals:
    void on_newMessages(DBMessageList&);
    void Write(QByteArray);

protected slots:
    void do_parseResponce(QByteArray buffer);

private:
    static const qint8 maxThreadCount;
    BackGroundWorker();

};
