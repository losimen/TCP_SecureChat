#ifndef REQUESTMETHODS_H
#define REQUESTMETHODS_H

#include <QString>


struct RequestMethods
{
    static const QString logIn;
    static const QString signUp;
    static const QString createChat;
    static const QString addMember;
    static const QString sendMessage;
    static const QString getMessageList;
    static const QString getChatList;

};


#endif // REQUESTMETHODS_H
