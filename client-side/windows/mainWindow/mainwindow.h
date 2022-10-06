#pragma once

#include "iwindow.h"
#include <QListWidgetItem>


namespace Ui {
class MainWindow;
}

class MainWindow : public IWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void do_parseResponce(QByteArray buffer);
    void do_listItemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;

    enum RequestTypes {
        getChats,
        getMessages
    };

    RequestTypes currentRequestType;
};
