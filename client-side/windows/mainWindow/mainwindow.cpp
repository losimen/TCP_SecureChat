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

    connect(ui->list_chats, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onListItemClickes(QListWidgetItem*)));
    connect(&ServerSocket::getInstance(), SIGNAL(on_respond(QByteArray)), this, SLOT(do_parseResponce(QByteArray)));

    ServerSocket::getInstance().write(data.serializeData());
    currentRequestType = RequestTypes::getChats;
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::do_parseResponce(QByteArray buffer)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(buffer);
    QJsonObject jsonObject = jsonDocument.object();

    QJsonArray arr = jsonObject["chatList"].toArray();

    if (currentRequestType == RequestTypes::getChats)
    {
        for (auto el: arr)
        {
            ui->list_chats->insertItem(0, el.toObject()["chatName"].toString() + "#" + QString::number(el.toObject()["id"].toInt()));

            DBModelChat chat;

            chat.id = el.toObject()["id"].toInt();
            chat.chatName = el.toObject()["chatName"].toString();
            chat.createdAt = el.toObject()["createdAt"].toString();
            chat.creatorId = el.toObject()["creatorId"].toInt();

            CacheEmulator::getInstance().insertChat(chat);
        }
    }


}


void MainWindow::onListItemClickes(QListWidgetItem *item)
{
    qDebug() << item->text();
}
