#include "myrunnable.h"

MyRunnable::MyRunnable()
{

}


void MyRunnable::run()
{
    if (!MyRunnable::socketDescriptor)
        return;

    QTcpSocket socket;
    socket.setSocketDescriptor(MyRunnable::socketDescriptor);

    socket.write("Hello world");
    socket.flush();
    socket.waitForBytesWritten();
    socket.close();
}
