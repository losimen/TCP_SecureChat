#include "statuscodes.h"


StatusCodesInterface::StatusCodesInterface()
{
    StatusCodesInterface::currentStatusCode = StatusCodes::notFound;
}


void StatusCodesInterface::setCurrentStatusCode(StatusCodes &toSet)
{
    StatusCodesInterface::currentStatusCode = toSet;
}


const StatusCodes &StatusCodesInterface::getCurrentStatusCode() const
{
    return StatusCodesInterface::currentStatusCode;
}

StatusCodesInterface StatusCodesInterface::operator=(StatusCodes &toSet)
{
    StatusCodesInterface::currentStatusCode = toSet;

    return *this;
}


StatusCodesInterface StatusCodesInterface::operator=(const StatusCodes &toSet)
{
    StatusCodesInterface::currentStatusCode = toSet;

    return *this;
}
