#pragma once

#include <QtGlobal>
#include <QThreadPool>
#include <QThread>


class BackGroundWorker: public QRunnable
{
public:
    static BackGroundWorker &getInstance();

    void startBackGroundTask();

protected:
    void run();

private:
    static const qint8 maxThreadCount;

    BackGroundWorker();
};
