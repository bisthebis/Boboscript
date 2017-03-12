#include "lexertest.h"
#include "scanner.h"
#include <QtTest/QtTest>

LexerTest::LexerTest(QObject *parent) : QObject(parent)
{

}

void LexerTest::initTestCase() {
}

void LexerTest::cleanupTestCase() {
}
Q_DECLARE_METATYPE(QVector<Token>)
void LexerTest::expectedTokenList_data() {
    QTest::addColumn<QString>("input");
    QTest::addColumn<QVector<Token>>("expected");

    static const QString funcDefInput = "function twice(Double x) -> Double {\n"
                                 "\treturn 2 * x;\n"
                                 "}";

    static const QVector<Token> funcDefExpected = {
        Token(Token::FUNCTION, "function", "function", 1, 9),
        Token(Token::IDENTIFIER, "twice", "twice", 1, 15),
        Token(Token::LEFT_PAREN, "(", "(", 1, 15),
        Token(Token::IDENTIFIER, "Double", "Double", 1, 22),
        Token(Token::IDENTIFIER, "x", "x", 1, 24),
        Token(Token::RIGHT_PAREN, ")", ")", 1, 24),
        Token(Token::ARROW, "->", "->", 1, 26),
        Token(Token::IDENTIFIER, "Double", "Double", 1, 35),
        Token(Token::LEFT_BRACKET, "{", "{", 1, 36),
        Token(Token::RETURN, "return", "return", 2, 7),
        Token(Token::INT_LIT, "2", 2, 2, 9),
        Token(Token::TIMES, "*", "*", 2, 10),
        Token(Token::IDENTIFIER, "x", "x", 2, 13),
        Token(Token::SEMICOLON, ";", ";", 2, 13),
        Token(Token::RIGHT_BRACKET, "}", "}", 3, 0),
    };

    static const QString nestedParenthesisInput = "((x) * (x))";
    static const QVector<Token> nestedParenthesisExpected = {
        Token(Token::LEFT_PAREN, "(", "(", 1, 1),
        Token(Token::LEFT_PAREN, "(", "(", 1, 2),
        Token(Token::IDENTIFIER, "x", "x", 1, 4),
        Token(Token::RIGHT_PAREN, ")", ")", 1, 4),
        Token(Token::TIMES, "*", "*", 1, 6),
        Token(Token::LEFT_PAREN, "(", "(", 1, 8),
        Token(Token::IDENTIFIER, "x", "x", 1, 10),
        Token(Token::RIGHT_PAREN, ")", ")", 1, 10),
        Token(Token::RIGHT_PAREN, ")", ")", 1, 11),
    };

    QTest::newRow("Function definition") << funcDefInput << funcDefExpected;
    QTest::newRow("Nested parenthesis") << nestedParenthesisInput << nestedParenthesisExpected;

}

void LexerTest::expectedTokenList() {

    QFETCH(QString, input);
    QFETCH(QVector<Token>, expected);

    auto scanner = Scanner::fromString(input);
    auto result = scanner.tokens();
    QCOMPARE(result.size(), expected.size());
    for (int i = 0; i < expected.size(); ++i)
    {
        QCOMPARE(result[i].type, expected[i].type);
        QCOMPARE(result[i].lexeme, expected[i].lexeme);
        QCOMPARE(result[i].value, expected[i].value);
        QCOMPARE(result[i].location.line, expected[i].location.line);
        QCOMPARE(result[i].location.column, expected[i].location.column);
    }

}
