#include "login.h"
#include "ui_login.h"
#include "clickable_qlabel.h"
#include "inputvalidator.h"
#include "clienterrors.h"
#include "servertypes.h"
#include "serversocket.h"
#include "statuscodes.h"
#include "cacheemulator.h"


LogIn::LogIn(QWidget *parent) :
    IWindow(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    this->setWindowTitle("Log in");

    ui->lineEdit_username->setStyleSheet("QLineEdit { border-radius: 5px; }");
    ui->lineEdit_password->setStyleSheet("QLineEdit { border-radius: 5px; }");
    ui->label_error->setVisible(false);

    connect(ui->label_signUp, SIGNAL(on_mousePressed()), this, SLOT(do_labelClicked()));
    connect(ui->pushButton,  SIGNAL(clicked()), this, SLOT(do_ButtonClicked()));
}


LogIn::~LogIn()
{
    delete ui;
}


void LogIn::do_labelClicked()
{
    emit on_openSignUpWindow();
}


void LogIn::do_ButtonClicked()
{
    ui->label_error->setVisible(false);
    ServerTypes::LogIn logIn_server;

    try
    {
        logIn_server = InputValidator::logIn(ui->lineEdit_username->text(),
                                             ui->lineEdit_password->text());
    }
    catch (ClientErrors::InvalidInput &err)
    {
        ui->label_error->setText(err.what());
        ui->label_error->setVisible(true);

        return;
    }

    CacheEmulator::getInstance().setCurrentUsername(logIn_server.username);

    connect(&ServerSocket::getInstance(), SIGNAL(on_respond(QByteArray)), this, SLOT(do_parseResponce(QByteArray)));
    connect(this, SIGNAL(on_write(QByteArray)), &ServerSocket::getInstance(), SLOT(write(QByteArray)));
    emit on_write(logIn_server.serializeData());
}


void LogIn::do_parseResponce(QByteArray buffer)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(buffer);
    QJsonObject jsonObject = jsonDocument.object();

    qint64 value = jsonObject["statusCode"].toInt();

    if (jsonObject["statusCode"].toInt() != StatusCodes::ok)
    {
       // TODO: print error
       return;
    }

    if (value == StatusCodes::ok)
    {
        CacheEmulator::getInstance().setAccessToken(jsonObject["accessToken"].toString());
        emit on_openMainWindow();
    }
    else
    {
        ui->label_error->setText(jsonObject["msg"].toString());
        ui->label_error->setVisible(true);
    }
}
