#pragma once

#include <QObject>

#include "login.h"
#include "signup.h"
#include "mainwindow.h"

#include "serversocket.h"


class WindowManager : public QObject
{
    Q_OBJECT

public:
    explicit WindowManager(QObject *parent = nullptr);

private slots:
    void do_LogInWindow();
    void do_SignUpWindow();
    void do_MainWindow();

private:
    std::unique_ptr<QWidget> currentWindow;

};
