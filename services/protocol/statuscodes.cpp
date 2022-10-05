#include "statuscodes.h"


StatusCodesWorker::StatusCodesWorker()
{
    StatusCodesWorker::currentStatusCode = StatusCodes::notFound;
}


void StatusCodesWorker::setCurrentStatusCode(StatusCodes &toSet)
{
    StatusCodesWorker::currentStatusCode = toSet;
}


const StatusCodes &StatusCodesWorker::getCurrentStatusCode() const
{
    return StatusCodesWorker::currentStatusCode;
}

StatusCodesWorker StatusCodesWorker::operator=(StatusCodes &toSet)
{
    StatusCodesWorker::currentStatusCode = toSet;

    return *this;
}


StatusCodesWorker StatusCodesWorker::operator=(const StatusCodes &toSet)
{
    StatusCodesWorker::currentStatusCode = toSet;

    return *this;
}
