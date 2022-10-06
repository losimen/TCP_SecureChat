#include "mainwindow.h"
#include "serversocket.h"
#include "servertypes.h"
#include "cacheemulator.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    IWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ServerTypes::GetChatList data;
    data.accessToken = CacheEmulator::getInstance().getAccessToken();
    data.offset = 0;

    connect(ui->list_chats, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(do_listItemClicked(QListWidgetItem*)));
    connect(&ServerSocket::getInstance(), SIGNAL(on_respond(QByteArray)), this, SLOT(do_parseResponce(QByteArray)));

    currentRequestType = RequestTypes::getChats;
    ServerSocket::getInstance().write(data.serializeData());
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::do_parseResponce(QByteArray buffer)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(buffer);
    QJsonObject jsonObject = jsonDocument.object();

    qDebug() << "here";

    if (currentRequestType == RequestTypes::getChats)
    {
        QJsonArray arr = jsonObject["chatList"].toArray();

        for (auto el: arr)
        {
            ClientModelChat chat;

            chat.id = el.toObject()["id"].toInt();
            chat.chatName = el.toObject()["chatName"].toString();
            chat.createdAt = el.toObject()["createdAt"].toString();
            chat.creatorId = el.toObject()["creatorId"].toInt();

            CacheEmulator::getInstance().insertChat(chat);

            ui->list_chats->insertItem(0, chat.getFullName());
        }
    }
    else if (currentRequestType == RequestTypes::getMessages)
    {
        QJsonArray arr = jsonObject["messageList"].toArray();

        for (auto el: arr)
        {
            ClientModelMessage message;

            message.id = el.toObject()["id"].toInt();
            message.msgText = el.toObject()["msgText"].toString();
            message.sendeUsername = el.toObject()["senderUsername"].toString();
            message.createdAt = el.toObject()["createdAt"].toString();
            message.chatId = el.toObject()["chatId"].toInteger();

           ui->list_messages->addItem(message.sendeUsername + ": " + message.msgText);
        }
    }

}


void MainWindow::do_listItemClicked(QListWidgetItem *item)
{
    ui->list_messages->clear();
    ServerTypes::GetMessageList data;
    data.accessToken = CacheEmulator::getInstance().getAccessToken();
    data.offset = 0;
    data.chatId = ClientModelChat::getChatIdFromFullName(item->text());

    currentRequestType = RequestTypes::getMessages;

    ServerSocket::getInstance().write(data.serializeData());
}
