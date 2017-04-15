#include "parsertest.h"
#include "fileast.h"
#include "scanner.h"
#include <QtTest/QtTest>

ParserTest::ParserTest(QObject *parent) : QObject(parent)
{

}

void ParserTest::initTestCase() {
}

void ParserTest::cleanupTestCase() {
}

void ParserTest::dummySuccess() {

}

Q_DECLARE_METATYPE(QVector<Token>)
Q_DECLARE_METATYPE(FileAST)
/*void ParserTest::expectedAST_data() {
    QTest::addColumn<QVector<Token>>("input");
    QTest::addColumn<FileAST>("expected");
    
    QVector<Tokens>

}*/

void ParserTest::expectedAST() {
    qDebug() << "MDR";
}
