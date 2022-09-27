#include <QCoreApplication>
#include "listener.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Listener listener;
    listener.startServer();

    return a.exec();
}
