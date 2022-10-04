#ifndef SERVERERRORS_H
#define SERVERERRORS_H

#include <QException>
#include <QString>
#include <QDebug>

#include "statuscodes.h"


namespace ServerErrors
{

class MyServerException: public QException {
protected:
    QString _what;
    StatusCodesInterface statusCode;

public:
    const char *what() const throw()
    {
        QByteArray ba = _what.toLocal8Bit();
        const char *what = ba.data();
        return what;
    }

    StatusCodes getStatusCode()
    {
        return statusCode.getCurrentStatusCode();
    }

    MyServerException(const QString &what)
    {
        MyServerException::_what = what;
    }

};

class InvalidFormat: public MyServerException
{
private:

public:
    InvalidFormat(const QString &what): MyServerException(what)
    {
        statusCode = StatusCodes::badRequest;
    }

};


class MissingArgument: public MyServerException
{
private:

public:
    MissingArgument(const QString &what): MyServerException(what)
    {
        statusCode = StatusCodes::badRequest;
    }

};


class NotFound: public MyServerException
{
private:

public:
    NotFound(const QString &what): MyServerException(what)
    {
        statusCode = StatusCodes::notFound;
    }

};


class Conflict: public MyServerException
{
private:


public:
    Conflict(const QString &what): MyServerException(what)
    {
        statusCode = StatusCodes::conflict;
    }

};

class Unauthorized: public MyServerException
{
private:

public:
    Unauthorized(const QString &what): MyServerException(what)
    {
        statusCode = StatusCodes::conflict;
    }

};

}



#endif // SERVERERRORS_H
