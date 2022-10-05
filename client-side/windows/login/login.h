#pragma once

#include "iwindow.h"


namespace Ui {
class LogIn;
}

class LogIn : public IWindow
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

protected slots:
    void do_labelClicked();
    void do_ButtonClicked();

    void do_parseResponce(QByteArray buffer);

private:
    Ui::LogIn *ui;
};
