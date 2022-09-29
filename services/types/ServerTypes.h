#ifndef SERVERTYPES_H
#define SERVERTYPES_H

#include <QtGlobal>
#include <QString>
#include <QJsonObject>


namespace ServerTypes
{

struct LogIn
{
    QString username;
    QString password;

    void parseData(const QString &username, const QString &password);
    QByteArray serializeData() const;

};


struct SignUp
{
    QString username;
    QString password;

    void parseData(const QString &username, const QString &password);
    QByteArray serializeData() const;
};

}




#endif // SERVERTYPES_H
