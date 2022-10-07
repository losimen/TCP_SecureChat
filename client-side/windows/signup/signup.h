#pragma once

#include "iwindow.h"


namespace Ui {
class SignUp;
}

class SignUp : public IWindow
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void do_labelClicked();
    void do_ButtonClicked();

    void do_parseResponce(QByteArray buffer);

private:
    Ui::SignUp *ui;

    enum RequestTypes {
        signUp,
        getPubKey
    };

    RequestTypes currentRequestType;
};
