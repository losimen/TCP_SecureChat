#include "signup.h"
#include "ui_signup.h"

SignUp::SignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);

    ui->lineEdit_username->setStyleSheet("QLineEdit { border-radius: 5px; }");
    ui->lineEdit_password->setStyleSheet("QLineEdit { border-radius: 5px; }");
    ui->lineEdit_password_2->setStyleSheet("QLineEdit { border-radius: 5px; }");

    connect(ui->label_logIn, SIGNAL(on_mousePressed()), this, SLOT(do_labelClicked()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(do_ButtonClicked()));

    this->setWindowTitle("Sign up");
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::do_labelClicked()
{
    emit SignUp::on_openLogInWindow();
}

void SignUp::do_ButtonClicked()
{
    qDebug() << "Pressed sign up";
}
