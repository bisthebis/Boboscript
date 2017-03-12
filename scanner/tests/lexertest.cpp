#include "lexertest.h"
#include <QtTest/QtTest>

LexerTest::LexerTest(QObject *parent) : QObject(parent)
{

}

void LexerTest::initTestCase() {
}

void LexerTest::cleanupTestCase() {
}

void LexerTest::succeed() {
    QVERIFY(true);
}
