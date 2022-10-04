#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>

#include "login.h"
#include "signup.h"


class WindowManager : public QObject
{
    Q_OBJECT

public:
    explicit WindowManager(QObject *parent = nullptr);


private slots:
    void open_LogInWindow();
    void open_SignUpWindow();

private:
    std::unique_ptr<QWidget> currentWindow;

};

#endif // WINDOWMANAGER_H
