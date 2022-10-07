#pragma once

#include "iwindow.h"


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
    void do_sendClicked();
    void do_newMessage(DBMessageList &msgList);

private:
    Ui::MainWindow *ui;

    enum RequestTypes {
        getChats,
        getMessages,
        sendMessage
    };

    RequestTypes currentRequestType;

    // TODO: in future list of pending messages
//    typedef std::map<std::string, QListWidgetItem*> MyMap;
//    typedef std::pair<std::string, QListWidgetItem*> MyPair;
    QMap<QString, QListWidgetItem*> messageQueue;
};
