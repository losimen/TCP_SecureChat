#include "windowmanager.h"
#include "login.h"
#include "signup.h"


WindowManager::WindowManager(QObject *parent)
    : QObject{parent}
{
    WindowManager::open_LogInWindow();
}


void WindowManager::open_LogInWindow()
{
    currentWindow.reset(new LogIn);
    connect(currentWindow.get(), SIGNAL(on_openSignUpWindow()), this, SLOT(open_SignUpWindow()));

    currentWindow->show();
}


void WindowManager::open_SignUpWindow()
{
    qDebug() << "here in WindowManager";
//    currentWindow = nullptr;
//    currentWindow.reset(new SignUp);
//    currentWindow->show();
}
