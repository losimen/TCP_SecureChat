#pragma once

#include <QWidget>

namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void do_labelClicked();
    void do_ButtonClicked();

signals:
    void on_openLogInWindow();

private:
    Ui::SignUp *ui;
};
