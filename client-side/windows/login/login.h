#pragma once

#include <QWidget>

namespace Ui {
class LogIn;
}

class LogIn : public QWidget
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

private slots:
    void do_labelClicked();
    void do_ButtonClicked();

signals:
    void on_openSignUpWindow();

private:
    Ui::LogIn *ui;
};
