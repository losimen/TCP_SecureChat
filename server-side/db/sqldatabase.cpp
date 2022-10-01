#include <QThread>
#include <QString>

#include "sqldatabase.h"
#include "dberrors.h"


void SQLDatabase::validateIsOpen()
{
    if (!SQLDatabase::db.isOpen())
    {
        qDebug() << db.lastError();
        throw DBErrors::Open("Error in connecting to the DB please contact admin.");
    }

}


void SQLDatabase::execQuery(QSqlQuery &query)
{
    if (!query.exec())
    {
        qDebug() << query.lastError();
        throw DBErrors::Exec("Error in executing request please contact admin.");
    }
}


SQLDatabase::SQLDatabase()
{
    qint32 *a = (int*)QThread::currentThreadId();
    SQLDatabase::db = QSqlDatabase::addDatabase("QMYSQL", QString::number((*a)));

    db.setHostName("localhost");
    db.setDatabaseName("SecureChat");
    db.setUserName("root");
    db.setPassword("zTmUHsbEKZZlWhfofM");

    db.open();
}


qint64 SQLDatabase::saveUser(const QString &username, const QString &password)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("INSERT INTO Users (Username, Password) "
                  "VALUES (:Username, :Password)");

    query.bindValue(":Username", username);
    query.bindValue(":Password", password);

    SQLDatabase::execQuery(query);

    return SQLDatabase::getUserIdByUsername(username);
}


qint64 SQLDatabase::getUserIdByAuth(const QString &username, const QString &password)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("SELECT ID FROM Users WHERE Username = :Username AND Password = :Password");
    query.bindValue(":Username", username);
    query.bindValue(":Password", password);

    SQLDatabase::execQuery(query);

    if (!query.first())
        throw DBErrors::GetValue("There is no such record");

    return query.value(0).toInt();
}


qint64 SQLDatabase::getUserIdByUsername(const QString &username)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("SELECT ID FROM Users WHERE Username = :Username");
    query.bindValue(":Username", username);

    SQLDatabase::execQuery(query);

    if (!query.first())
        throw DBErrors::GetValue("There is no such record");

    return query.value(0).toInt();
}


QString SQLDatabase::generateAccessToken(const qint64 userId)
{
    // TODO: use SHA256
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);
    QString accessToken = "accessToken_" + QString::number(userId);

    query.prepare("INSERT INTO AccessTokens (AccessToken, UserID) "
                  "VALUES (:AccessToken, :UserID)");

    query.bindValue(":AccessToken", accessToken);
    query.bindValue(":UserID", userId);

    SQLDatabase::execQuery(query);

    return accessToken;
}


QString SQLDatabase::getUserAccessToken(const qint64 userId)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("SELECT AccessToken FROM AccessTokens WHERE UserID = :UserID");
    query.bindValue(":UserID", userId);

    SQLDatabase::execQuery(query);

    if (!query.first())
        throw DBErrors::GetValue("There is no such record");

    return query.value(0).toString();
}


SQLDatabase::~SQLDatabase()
{
    qint32 *a = (int*)QThread::currentThreadId();

    db.close();
    db = QSqlDatabase();

    QSqlDatabase::removeDatabase(QString::number((*a)));
}
