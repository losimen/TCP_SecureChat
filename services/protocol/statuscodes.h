#pragma once

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


class StatusCodesWorker
{
private:
    StatusCodes currentStatusCode;

public:
    StatusCodesWorker();

    void setCurrentStatusCode(StatusCodes &toSet);
    const StatusCodes &getCurrentStatusCode() const;

    StatusCodesWorker operator=(const StatusCodes &toSet);
};
