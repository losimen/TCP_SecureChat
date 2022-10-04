#ifndef LOGIN_H
#define LOGIN_H

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

signals:
    void on_openSignUpWindow();

private slots:
    void button_clicked();

private:
    Ui::LogIn *ui;
};

#endif // LOGIN_H
