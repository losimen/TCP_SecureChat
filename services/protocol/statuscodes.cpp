#include "statuscodes.h"

const QString StatusCodes::OK = "OK";
const QString StatusCodes::FAIL = "FAIL";


void StatusCodes::setCurrentStatusCode(QString &toSet)
{
    StatusCodes::currentStatusCode = toSet;
}

const QString &StatusCodes::getCurrentStatusCode() const
{
    return currentStatusCode;
}
