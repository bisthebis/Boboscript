#include <QtCore>
#include <QtTest/QtTest>
#include "parsertest.h"

int main(int argc, char** argv) {
    int status = 0;
    {
        ParserTest t;
        status |= QTest::qExec(&t, argc, argv);
    }


    return status;
}
