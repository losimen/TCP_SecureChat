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


void CacheEmulator::setAccessToken(const QString &accessToken)
{
    this->accessToken = accessToken;
}


void CacheEmulator::insertChat(const DBModelChat &chat)
{
    chatList.push_back(chat);
}


CacheEmulator::CacheEmulator()
{

}
