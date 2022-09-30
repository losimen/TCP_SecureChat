#ifndef SERVERERRORS_H
#define SERVERERRORS_H

#include <QException>
#include <QString>
#include <QDebug>

namespace ServerErrors
{

class InvalidFormat: public QException
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


class MissingArgument: public QException
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


class NotFound: public QException
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
