#include "parsertest.h"
#include "fileast.h"
#include "parser.h"
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
        auto scanner = Scanner::fromJson(doc);
        auto tokens = scanner.tokens();

        //Now that we have the tokens, we can parse then compare to expected AST (TODO)

        Parser parser(tokens);

        qDebug() << "Log of parser : " << parser.getLog();
    }
    catch (MyException& e) {
        QFAIL(QString("Exception catched in test : %1").arg(e.msg).toStdString().data());
    }
}
