#include "parsertest.h"
#include "fileast.h"
#include "scanner.h"
#include "myexception.h"
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

Q_DECLARE_METATYPE(FileAST)
void ParserTest::expectedAST_data() {
    QTest::addColumn<QString>("input"); //QRC file
    //QTest::addColumn<FileAST>("expected");
    
    QTest::newRow("Sample 1") << ":/sample_1_tokens.json";

}

void ParserTest::expectedAST() {
    QFETCH(QString, input);
    try {
        QFile file(input);
        QVERIFY(file.open(QFile::ReadOnly));
        QByteArray data = file.readAll();
        auto doc = QJsonDocument::fromJson(data);
        auto tokens = Scanner::fromJson(doc);
        //Now that we have the tokens, we can compare to expected AST (TODO)

        qDebug() << "Number of tokens : " << tokens.tokens().size();
    }
    catch (MyException& e) {
        QFAIL(QString("Exception catched in test : %1").arg(e.msg).toStdString().data());
    }
}
