#ifndef SERVERTYPES_H
#define SERVERTYPES_H

#include <QtGlobal>
#include <QString>
#include <QJsonObject>


namespace ServerTypes {

struct LogIn {
    qint64 user_id;
    QString password;

    LogIn parseData(QJsonObject jsonObject);
};


struct SignUp {
    qint64 user_id;
    QString password;
};

}




#endif // SERVERTYPES_H
