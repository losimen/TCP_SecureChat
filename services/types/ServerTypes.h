#ifndef SERVERTYPES_H
#define SERVERTYPES_H

#include <QtGlobal>
#include <QString>
#include <QJsonObject>


namespace ServerTypes
{

struct LogIn
{
private:
    QString username;
    QString password;

public:
    void parseData(const QString &username, const QString &password);
    QByteArray serializeData() const;

};


struct SignUp
{
private:
    QString username;
    QString password;

public:
    void parseData(const QString &username, const QString &password);
    QByteArray serializeData() const;

};

}




#endif // SERVERTYPES_H
