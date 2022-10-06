#include "backgroundworker.h"

qint8 const BackGroundWorker::maxThreadCount = 3;


BackGroundWorker &BackGroundWorker::getInstance()
{
    static BackGroundWorker object;
    return object;
}


void BackGroundWorker::run()
{
    while(true)
    {
        QThread::msleep(1);
    }
}


BackGroundWorker::BackGroundWorker()
{
    QThreadPool::globalInstance()->setMaxThreadCount(maxThreadCount);
}
