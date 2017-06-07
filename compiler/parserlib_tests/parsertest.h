#ifndef LEXERTEST_H
#define LEXERTEST_H

#include <QObject>

class ParserTest : public QObject
{
    Q_OBJECT
public:
    explicit ParserTest(QObject *parent = 0);

private slots:
    void initTestCase();
    void dummySuccess();

    void expectedAST_data();
    void expectedAST();

    void enumTest();
    void structTest();

    void cleanupTestCase();
};

#endif // LEXERTEST_H
