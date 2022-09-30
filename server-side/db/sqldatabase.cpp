#include "sqldatabase.h"
#include "dberrors.h"


void SQLDatabase::validateIsOpen()
{
    if (!SQLDatabase::db.isOpen())
        throw DBErrors::Open(db.lastError().text());
}


void SQLDatabase::validateIsSucess()
{

}


SQLDatabase::SQLDatabase()
{
    SQLDatabase::db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setDatabaseName("SecureChat");
    db.setUserName("root");
    db.setPassword("zTmUHsbEKZZlWhfofM");

    db.open();
}


qint64 SQLDatabase::saveUser(const QString &username, const QString &password)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query;

    query.prepare("INSERT INTO Users (Username, Password) "
                  "VALUES (:Username, :Password)");

    query.bindValue(":Username", username);
    query.bindValue(":Password", password);

    query.exec();

    return SQLDatabase::getUserIdByUsername(username);
}


qint64 SQLDatabase::getUserIdByUsername(const QString &username)
{
    SQLDatabase::validateIsOpen();

    QSqlQuery query;

    bool isSucess = query.exec("SELECT ID FROM Users WHERE Username = :Username");
    query.bindValue(":Username", username);    

    return query.first();
}


QString SQLDatabase::generateAccessToken(const qint64 userId)
{
    // TODO: use SHA256
    SQLDatabase::validateIsOpen();

    QSqlQuery query;
    QString accessToken = "accessToken";

    query.prepare("INSERT INTO AccessTokens (AccessToken, UserID) "
                  "VALUES (:AccessToken, :UserID)");

    query.bindValue(":AccessToken", accessToken);
    query.bindValue(":UserID", userId);

    return accessToken;
}


SQLDatabase::~SQLDatabase()
{
    db.close();
    db.removeDatabase("QMYSQL");
}
