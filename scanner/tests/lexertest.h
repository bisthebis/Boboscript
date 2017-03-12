#ifndef LEXERTEST_H
#define LEXERTEST_H

#include <QObject>

class LexerTest : public QObject
{
    Q_OBJECT
public:
    explicit LexerTest(QObject *parent = 0);

private slots:
    void initTestCase();
    void expectedTokenList();
    void cleanupTestCase();
};

#endif // LEXERTEST_H
