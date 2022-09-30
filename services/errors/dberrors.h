#ifndef DBERRORS_H
#define DBERRORS_H

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

}


#endif // DBERRORS_H
