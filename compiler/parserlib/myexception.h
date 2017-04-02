#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <QException>

class MyException : public QException
{
public:
    const QString msg;
    MyException(QString msg) : msg("MyException occured : " + msg){}

    virtual void raise() const {throw *this;}
    MyException* clone() const {return new MyException(*this);}
};

#endif // MYEXCEPTION_H
