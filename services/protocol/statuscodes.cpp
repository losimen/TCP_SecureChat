#include "statuscodes.h"


StatusCodesWorker::StatusCodesWorker()
{
    currentStatusCode = StatusCodes::notFound;
}


void StatusCodesWorker::setCurrentStatusCode(StatusCodes &toSet)
{
    currentStatusCode = toSet;
}


const StatusCodes &StatusCodesWorker::getCurrentStatusCode() const
{
    return currentStatusCode;
}


StatusCodesWorker StatusCodesWorker::operator=(const StatusCodes &toSet)
{
    currentStatusCode = toSet;

    return *this;
}
