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

    QString putTagInQuotes(const QString &name) const;
    QString putStrInQuotes(const QString &name) const;

    QString serializeMsgList(MessageList &list) const;
    QString serializeChatList(ChatList &list) const;
};
