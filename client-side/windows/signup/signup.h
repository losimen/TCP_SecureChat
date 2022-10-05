#pragma once

#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>


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

    void do_parseResponce(QByteArray buffer);

signals:
    void on_openLogInWindow();
    void on_openMainWindow();

private:
    Ui::SignUp *ui;
};
