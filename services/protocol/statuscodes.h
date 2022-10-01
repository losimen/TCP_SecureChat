#ifndef STATUSCODES_H
#define STATUSCODES_H

#include <QString>
#include <QMap>


enum StatusCodes {
    badRequest = 400,
    unathorized = 401,
    notFound = 404,
    conflict = 409,
    ok = 200,
    internalError = 500,
    serviceUnavalibale = 503
};


class StatusCodesInterface
{
private:
    StatusCodes currentStatusCode;

public:
    StatusCodesInterface();

    void setCurrentStatusCode(StatusCodes &toSet);
    const StatusCodes &getCurrentStatusCode() const;

    StatusCodesInterface operator=(StatusCodes &toSet);
    StatusCodesInterface operator=(const StatusCodes &toSet);
};

#endif // STATUSCODES_H
