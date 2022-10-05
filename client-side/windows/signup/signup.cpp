#include "signup.h"
#include "ui_signup.h"
#include "inputvalidator.h"
#include "clienterrors.h"
#include "servertypes.h"
#include "serversocket.h"


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
    ui->label_error->setVisible(false);
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

    connect(&ServerSocket::getInstance(), SIGNAL(on_respond(QByteArray)), this, SLOT(do_parseResponce(QByteArray)));
    ServerSocket::getInstance().write(signUp_server.serializeData());
}



void SignUp::do_parseResponce(QByteArray buffer)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(buffer);
    QJsonObject jsonObject = jsonDocument.object();

    qint64 value = jsonObject["statusCode"].toInt();

    if (value == StatusCodes::ok)
    {
        emit on_openMainWindow();
    }
    else
    {
        ui->label_error->setText(jsonObject["msg"].toString());
        ui->label_error->setVisible(true);
    }
}
