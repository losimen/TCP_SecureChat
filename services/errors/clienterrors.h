#pragma once

#include <QException>
#include <QString>
#include <QDebug>

namespace ClientErrors
{

class InvalidInput: public QException
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

    InvalidInput(const QString &what)
    {
        InvalidInput::_what = what;
    }
};

}
