#include "clientmodelchat.h"

#include <QDebug>


const QString ClientModelChat::getFullName()
{
    return QString("%1#%2").arg(chatName,
                                QString::number(id));
}


const qint64 ClientModelChat::getChatIdFromFullName(const QString &buffer)
{
    return buffer.split('#')[1].toULongLong();
}
