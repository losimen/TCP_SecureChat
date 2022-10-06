#pragma once

#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QListWidgetItem>

#include "inputvalidator.h"


class IWindow : public QWidget
{
    Q_OBJECT
public:
    explicit IWindow(QWidget *parent = nullptr);

protected slots:
    virtual void do_parseResponce(QByteArray buffer) = 0;

signals:
    void on_openLogInWindow();
    void on_openMainWindow();
    void on_openSignUpWindow();
    void on_write(QByteArray);

};
