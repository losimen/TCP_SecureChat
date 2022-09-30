#include <QThread>
#include <QString>

#include "sqldatabase.h"
#include "dberrors.h"


void SQLDatabase::validateIsOpen()
{
    if (!SQLDatabase::db.isOpen())
        throw DBErrors::Open(db.lastError().text());
}


void SQLDatabase::execQuery(QSqlQuery &query)
{
    if (!query.exec())
        qDebug() << "Error in executing request: " + query.lastError().text();
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

    query.first();

    return query.value(0).toInt();
}


qint64 SQLDatabase::getUserIdByUsername(const QString &username)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query(SQLDatabase::db);

    query.prepare("SELECT ID FROM Users WHERE Username = :Username");
    query.bindValue(":Username", username);

    SQLDatabase::execQuery(query);

    query.first();
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

    query.first();
    return query.value(0).toString();
}


SQLDatabase::~SQLDatabase()
{
    qint32 *a = (int*)QThread::currentThreadId();

    db.close();
    db = QSqlDatabase();

    QSqlDatabase::removeDatabase(QString::number((*a)));
}
