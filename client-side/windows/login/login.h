#pragma once

#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>


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

    void do_parseResponce(QByteArray buffer);

signals:
    void on_openSignUpWindow();
    void on_openMainWindow();

private:
    Ui::LogIn *ui;
};
