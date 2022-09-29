#ifndef SERVERERRORS_H
#define SERVERERRORS_H

#include <exception>

#include <QString>
#include <QDebug>

namespace ServerErrors
{

class InvalidFormat: public std::exception
{
private:
    QString _what;

public:
    const char *what() const throw()
    {
        QByteArray ba = _what.toLocal8Bit();
        const char *what = ba.data();
        return what;
    }

    InvalidFormat(const QString &what)
    {
        InvalidFormat::_what = what;
    }
};


class MissingArgument: public std::exception
{
private:
    QString argName;

public:
    const char *what() const throw()
    {
        QByteArray ba = argName.toLocal8Bit();
        const char *what = ba.data();
        return what;
    }

    MissingArgument(const QString &argName)
    {
        MissingArgument::argName = "Missing argument: " + argName;
    }
};


class NotFound: public std::exception
{
private:
    QString argName;

public:
    const char *what() const throw()
    {
        QByteArray ba = argName.toLocal8Bit();
        const char *what = ba.data();
        return what;
    }

    NotFound(const QString &argName)
    {
        NotFound::argName = argName;
    }
};


}



#endif // SERVERERRORS_H
