#pragma once

#include <QtGlobal>

#include "statuscodes.h"
#include "dbmodelmessage.h"
#include "dbmodelchat.h"

// Param with '_' at the beginning are additional information parameters
// and not used for serialazation and parsing

struct IType {
public:
    virtual QByteArray serializeData() const = 0;

    QString serializeMsgList(DBMessageList &list) const;
    QString serializeChatList(DBChatList &list) const;
};
