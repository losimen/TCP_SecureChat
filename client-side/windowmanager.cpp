#include "windowmanager.h"
#include "login.h"
#include "signup.h"
#include "serversocket.h"


WindowManager::WindowManager(QObject *parent)
    : QObject{parent}
{
    ServerSocket::getInstance().connectToHost("127.0.0.1", qint16(54000));

    WindowManager::do_LogInWindow();
}


void WindowManager::do_LogInWindow()
{
    currentWindow.reset(new LogIn);

    connect(currentWindow.get(), SIGNAL(on_openSignUpWindow()), this, SLOT(do_SignUpWindow()));

    currentWindow->show();
}


void WindowManager::do_SignUpWindow()
{
    currentWindow.reset(new SignUp);

    connect(currentWindow.get(), SIGNAL(on_openLogInWindow()), this, SLOT(do_LogInWindow()));

    currentWindow->show();
}
