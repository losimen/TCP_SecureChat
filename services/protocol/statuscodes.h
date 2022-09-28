#ifndef STATUSCODES_H
#define STATUSCODES_H

#include <QString>


struct StatusCodes
{
private:
    const QString currentStatusCode;

public:
    static const QString OK;
    static const QString FAIL;

    void setCurrentStatusCode(QString &toSet);
    const QString &getCurrentStatusCode() const;
};

#endif // STATUSCODES_H
