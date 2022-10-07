#include "cacheemulator.h"


CacheEmulator &CacheEmulator::getInstance()
{
    static CacheEmulator object;
    return object;
}


const QString CacheEmulator::getAccessToken()
{
    return accessToken;
}

const QString CacheEmulator::getCurrentUsername()
{
    return currentUser.username;
}


const qint64 CacheEmulator::getLastMessageId()
{
    return lastMessageId;
}


void CacheEmulator::setAccessToken(const QString &accessToken)
{
    this->accessToken = accessToken;
}


void CacheEmulator::setCurrentUsername(const QString &username)
{
    this->currentUser.username = username;
}


void CacheEmulator::setLastMessageId(const qint64 &lastMessageId)
{
    this->lastMessageId = lastMessageId;
}


void CacheEmulator::insertChat(const DBModelChat &chat)
{
    chatList.push_back(chat);
}


void CacheEmulator::insertMessage(const DBModelMessage &message)
{
    messageList.push_back(message);
}


const QString CacheEmulator::getChatFullName(const QString &chatName, const qint64 chatId)
{
    return QString("%1#%2").arg(chatName,
                                QString::number(chatId));
}


const qint64 CacheEmulator::getChatIdFromFullName(const QString &buffer)
{
    return buffer.split('#')[1].toULongLong();
}


CacheEmulator::CacheEmulator()
{
    lastMessageId = 0;
}

const QString &CacheEmulator::getServerPubKey() const
{
    return serverPubKey;
}

void CacheEmulator::setServerPubKey(const QString &newServerPubKey)
{
    serverPubKey = newServerPubKey;
}
