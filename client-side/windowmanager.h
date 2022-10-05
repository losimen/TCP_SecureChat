#pragma once

#include <QObject>

#include "login.h"
#include "signup.h"
#include "serversocket.h"


class WindowManager : public QObject
{
    Q_OBJECT

public:
    explicit WindowManager(QObject *parent = nullptr);

private slots:
    void do_LogInWindow();
    void do_SignUpWindow();

private:
    std::unique_ptr<QWidget> currentWindow;

};
