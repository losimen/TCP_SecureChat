#include "signup.h"
#include "ui_signup.h"
#include "inputvalidator.h"
#include "clienterrors.h"
#include "servertypes.h"


SignUp::SignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);

    ui->lineEdit_username->setStyleSheet("QLineEdit { border-radius: 5px; }");
    ui->lineEdit_password->setStyleSheet("QLineEdit { border-radius: 5px; }");
    ui->lineEdit_password_2->setStyleSheet("QLineEdit { border-radius: 5px; }");

    ui->label_error->setVisible(false);
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
    ServerTypes::SignUp signUp_server;

    try
    {
        signUp_server = InputValidator::signUp(ui->lineEdit_username->text(),
                                             ui->lineEdit_password->text(),
                                             ui->lineEdit_password_2->text());
    }
    catch (ClientErrors::InvalidInput &err)
    {
        ui->label_error->setText(err.what());
        ui->label_error->setVisible(true);

        return;
    }


    qDebug() << signUp_server.username;
    qDebug() << signUp_server.password;
}
