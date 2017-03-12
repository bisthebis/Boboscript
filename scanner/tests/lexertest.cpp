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

void LexerTest::expectedTokenList() {
    static const QString input = "function twice(Double x) -> Double {\n"
                                 "\treturn 2 * x;\n"
                                 "}";

    static const QVector<Token> expected = {
        Token(Token::FUNCTION, "function", "function", 1, 9),
        Token(Token::IDENTIFIER, "twice", "twice", 1, 15),
        Token(Token::LEFT_PAREN, "(", "(", 1, 15),
        Token(Token::IDENTIFIER, "Double", "Double", 1, 22),
        Token(Token::IDENTIFIER, "x", "x", 1, 24),
        Token(Token::RIGHT_PARENT, ")", ")", 1, 24),
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

    auto scanner = Scanner::fromString(input);
    auto result = scanner.tokens();
    QCOMPARE(result.size(), expected.size());
    for (int i = 0; i < expected.size(); ++i)
    {
        QCOMPARE(expected[i].type, result[i].type);
        QCOMPARE(expected[i].lexeme, result[i].lexeme);
        QCOMPARE(expected[i].value, result[i].value);
        QCOMPARE(expected[i].location.line, result[i].location.line);
        QCOMPARE(expected[i].location.column, result[i].location.column);
    }

}
