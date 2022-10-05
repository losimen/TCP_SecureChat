#include "servertypes.h"

using namespace ServerTypes;


QByteArray LogIn::serializeData() const
{
    return QByteArray();
}


QByteArray SignUp::serializeData() const
{
    return QByteArray();
}


QByteArray CreateChat::serializeData() const
{
    return QByteArray();
}


QByteArray AddMember::serializeData() const
{
    return QByteArray();
}


QByteArray SendMessage::serializeData() const
{
    return QByteArray();
}


QByteArray GetMessageList::serializeData() const
{
    return QByteArray();
}


QByteArray GetChatList::serializeData() const
{
    return QByteArray();
}
