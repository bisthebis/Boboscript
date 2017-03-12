#include <QtCore>
#include <QtTest/QtTest>
#include "lexertest.h"

int main(int argc, char** argv) {
    int status = 0;
    {
        LexerTest t;
        status |= QTest::qExec(&t, argc, argv);
    }


    return status;
}
