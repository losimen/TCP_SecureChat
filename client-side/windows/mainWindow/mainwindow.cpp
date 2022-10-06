#include "mainwindow.h"
#include "serversocket.h"
#include "servertypes.h"
#include "cacheemulator.h"
#include "ui_mainwindow.h"
#include "backgroundworker.h"


MainWindow::MainWindow(QWidget *parent) :
    IWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&BackGroundWorker::getInstance(), SIGNAL(on_newMessages(std::unique_ptr<DBMessageList>&)),
            this, SLOT(do_newMessage(std::unique_ptr<DBMessageList>&)));
    QThreadPool::globalInstance()->start(&BackGroundWorker::getInstance());

    ServerTypes::GetChatList data;
    data.accessToken = CacheEmulator::getInstance().getAccessToken();
    data.offset = 0;

    connect(ui->list_chats, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(do_listItemClicked(QListWidgetItem*)));
    connect(ui->button_send,  SIGNAL(clicked()), this, SLOT(do_sendClicked()));

    currentRequestType = RequestTypes::getChats;
    connect(&ServerSocket::getInstance(), SIGNAL(on_respond(QByteArray)), this, SLOT(do_parseResponce(QByteArray)));

    connect(this, SIGNAL(on_write(QByteArray)), &ServerSocket::getInstance(), SLOT(write(QByteArray)));
    emit on_write(data.serializeData());
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::do_parseResponce(QByteArray buffer)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(buffer);
    QJsonObject jsonObject = jsonDocument.object();

    if (jsonObject["statusCode"].toInt() != StatusCodes::ok)
    {
       // TODO: print UI error
       return;
    }

    if (jsonObject.find("isUpdate") != jsonObject.constEnd())
         return;

    if (currentRequestType == RequestTypes::getChats)
    {
        QJsonArray arr = jsonObject["chatList"].toArray();

        for (auto el: arr)
        {
            DBModelChat chat;

            chat.id = el.toObject()["id"].toInt();
            chat.chatName = el.toObject()["chatName"].toString();
            chat.createdAt = el.toObject()["createdAt"].toString();
            chat.creatorId = el.toObject()["creatorId"].toInt();

            CacheEmulator::getInstance().insertChat(chat);

            ui->list_chats->insertItem(0, CacheEmulator::getChatFullName(chat.chatName, chat.id));
        }
    }
    else if (currentRequestType == RequestTypes::getMessages)
    {
        QJsonArray arr = jsonObject["messageList"].toArray();
        qint64 lastId = 0;

        for (auto el: arr)
        {
            DBModelMessage message;

            message.id = el.toObject()["id"].toInt();
            message.msgText = el.toObject()["msgText"].toString();
            message.sendeUsername = el.toObject()["senderUsername"].toString();
            message.createdAt = el.toObject()["createdAt"].toString();
            message.chatId = el.toObject()["chatId"].toInteger();

            QListWidgetItem *item = new QListWidgetItem();
            item->setText(QString("%1: %2").arg(message.sendeUsername,
                                               message.msgText));

            item->setBackground(QBrush(QColor::fromRgbF(77, 120, 180, 0.7)));
            ui->list_messages->addItem(item);
            lastId = message.id;
        }

        CacheEmulator::getInstance().setLastMessageId(lastId);
    }
    else if (currentRequestType == RequestTypes::sendMessage)
    {
        messageQueue.begin().value()->setText(QString("%1: %2").arg(CacheEmulator::getInstance().getCurrentUsername(),
                                                                    messageQueue.begin().key()));
        messageQueue.remove(messageQueue.begin().key());
    }

}


void MainWindow::do_listItemClicked(QListWidgetItem *item)
{
    ui->list_messages->clear();
    ServerTypes::GetMessageList data;
    data.accessToken = CacheEmulator::getInstance().getAccessToken();
    data.offset = 0;
    data.chatId = CacheEmulator::getChatIdFromFullName(item->text());

    currentRequestType = RequestTypes::getMessages;

    emit on_write(data.serializeData());
}


void MainWindow::do_sendClicked()
{
    ServerTypes::SendMessage data = InputValidator::sendMessage(ui->lineEdit->text());
    data.accessToken = CacheEmulator::getInstance().getAccessToken();
    data.chatId = CacheEmulator::getChatIdFromFullName(ui->list_chats->currentItem()->text());

    currentRequestType = RequestTypes::sendMessage;

    emit on_write(data.serializeData());

    ui->lineEdit->clear();

    QListWidgetItem *item = new QListWidgetItem();
    messageQueue[data.msgText] = item;

    messageQueue[data.msgText]->setText("sending...");
    ui->list_messages->addItem(messageQueue[data.msgText]);
}


void MainWindow::do_newMessage(std::unique_ptr<DBMessageList> &msgList)
{
    qint64 lastId = 0;
    CacheEmulator::getInstance().setLastMessageId(lastId);

    for (auto &message: msgList->toList())
    {
        qDebug() << "newMs:" << message.msgText;
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(QString("%1: %2").arg(message.sendeUsername,
                                            message.msgText));

        item->setBackground(QBrush(QColor::fromRgbF(77, 120, 180, 0.7)));
        ui->list_messages->addItem(item);
        lastId = message.id;
    }

    CacheEmulator::getInstance().setLastMessageId(lastId);
}
