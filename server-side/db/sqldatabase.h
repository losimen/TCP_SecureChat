#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <QtSql>
#include <QDebug>
#include <QString>


class SQLDatabase
{
private:
    QSqlDatabase db;
    bool ok;

    void validateIsOpen();
    void execQuery(QSqlQuery &query);

public:
    SQLDatabase();

    qint64 saveUser(const QString &username, const QString &password);
    qint64 getUserIdByAuth(const QString &username, const QString &password);
    qint64 getUserIdByUsername(const QString &username);
    QString generateAccessToken(const qint64 userId);
    QString getUserAccessToken(const qint64 userId);

    ~SQLDatabase();
};

#endif // SQLDATABASE_H
