#include "login.h"
#include "ui_login.h"

LogIn::LogIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogIn)
{

    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &LogIn::button_clicked);

}


LogIn::~LogIn()
{
    delete ui;
}


void LogIn::button_clicked()
{
    qDebug() << "here in logIn";
    emit LogIn::on_openSignUpWindow();
}
