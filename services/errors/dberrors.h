#pragma once

#include <QException>


namespace DBErrors {

class Open: public QException
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

    Open(const QString &what)
    {
        Open::_what = what;
    }
};


class Exec: public QException
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

    Exec(const QString &what)
    {
        Exec::_what = what;
    }
};


class GetValue: public QException
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

    GetValue(const QString &what)
    {
        GetValue::_what = what;
    }
};



}
