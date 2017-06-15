#ifndef COMPOUND_TYPE_TEST_H
#define COMPOUND_TYPE_TEST_H

#include <QObject>

class CompoundTypeTest : public QObject
{
    Q_OBJECT
public:
    CompoundTypeTest();

private slots:
    void enumConversion();
};

#endif // COMPOUND_TYPE_TEST_H
