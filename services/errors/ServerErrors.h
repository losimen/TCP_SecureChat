#ifndef SERVERERRORS_H
#define SERVERERRORS_H

#include <exception>

#include <QString>
#include <QDebug>

namespace ServerErrors
{

class InvalidFormat : public std::exception
{
public:
    const char *what() const throw()
    {
        return "\r\nInvalid JSON format\r\n";
    }

    InvalidFormat() {}
};


class MissingArgument : public std::exception
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

}



#endif // SERVERERRORS_H
