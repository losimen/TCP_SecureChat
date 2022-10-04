#include "login.h"
#include "ui_login.h"
#include "clickable_qlabel.h"


LogIn::LogIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    this->setWindowTitle("Log in");

    ui->lineEdit_username->setStyleSheet("QLineEdit { border-radius: 5px; }");
    ui->lineEdit_password->setStyleSheet("QLineEdit { border-radius: 5px; }");

    connect(ui->label_signUp, SIGNAL(on_mousePressed()), this, SLOT(do_labelClicked()));
    connect(ui->pushButton,  SIGNAL(clicked()), this, SLOT(do_ButtonClicked()));
}


LogIn::~LogIn()
{
    delete ui;
}


void LogIn::do_labelClicked()
{
    emit LogIn::on_openSignUpWindow();
}


void LogIn::do_ButtonClicked()
{
    qDebug() << ui->lineEdit_username->text();
    qDebug() << ui->lineEdit_password->text();
}
