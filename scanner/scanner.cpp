#include "scanner.h"
#include "myexception.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>

Scanner::Scanner(const QString& sourcePath) {
    QFile file(sourcePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw MyException(QString("Couldn't not open file %1. Error is : %2.").arg(sourcePath).arg(file.errorString()));

    QTextStream stream(&file);
    fileContent = stream.readAll();
}

QChar Scanner::peek() const {
    return fileContent.at(currentChar);
}

QChar Scanner::next() const {
    return fileContent.at(currentChar + 1);
}

void Scanner::advance() {
    QChar current = peek();
    ++currentChar;
    if (current == QChar::LineFeed || current == QChar::LineSeparator)
    {
        ++currentLine;
        currentRow = 0;
    }
    else
    {
        ++currentRow;
    }
}

void Scanner::skipComment() {
    //Assumes the first character hasn't been consumed. Expects either "//" or "/*"
    QChar first = peek();
    QChar second = next();
    advance(); advance();

    if (first != '/')
        throw MyException(QString("Error on parsing comment. Line %1, row %2").arg(currentLine).arg(currentRow));

    if (second == '/') //One line comment
    {
        QChar c = peek(); advance();
        do {
            c = peek(); advance();
        } while (c != QChar::LineFeed && c != QChar::LineSeparator);
        return ;
    }
    else if (second == '*')
    {
        QChar c = peek(); advance();
        while (true)
        {
            c = peek(); advance();
            if (c == '*' && peek() == '/')
            {
                advance();
                return;
            }
        }
    }

    throw MyException(QString("Incorrect comment. Character following '/' is %1.").arg(second));
}

Token Scanner::parseCharLiteral() {
    QChar first = peek(); advance();
    QChar second = peek(); advance();
    if (first != '\'')
        throw MyException("Incorrect character literal. Doesn't start with \'");

    if (second == '\\')
        throw MyException("Escaped characters are not implemented yet");

    if (peek() != '\'')
        throw MyException("Incorrect character literal. Doesn't end with \'");

    advance();
    QString lexeme(second);
    return Token(Token::CHAR_LIT, lexeme, second, currentLine, currentRow);

}

Token Scanner::parseStringLiteral() {
    if (peek() != '"')
        throw MyException("String not starting with double quotes");

    advance();
    QString lexeme;
    while (peek() != '"')
    {
        lexeme += peek();
        if (peek() == '\\')
            throw MyException("Escaped characters are not implemented yet");

        advance();
    }
    advance();
    return Token(Token::STR_LIT, lexeme, lexeme, currentLine, currentRow);
}

Token Scanner::parseNumberLiteral() {
    QString lexeme = peek(); advance();
    QChar current = peek();
    bool isInteger = true;
    while (current.isDigit() || current == '.')
    {
        if (current == '.')
            isInteger = false;
        lexeme += current;
        advance();
        current = peek();
    }

    if (isInteger)
        return Token(Token::INT_LIT, lexeme, lexeme.toULongLong(), currentLine, currentRow);
    else
        return Token(Token::DOUBLE_LIT, lexeme, lexeme.toDouble(), currentLine, currentRow);

}

Token Scanner::parseAlphaNum() {
    QString lexeme = peek(); advance();
    QChar current = peek();
    while (current.isDigit() || current.isLetter() || current == '_')
    {
        lexeme += current;
        advance();
        current = peek();
    }

    //TODO : is it a keyword ?
    return Token(Token::IDENTIFIER, lexeme, lexeme, currentLine, currentRow);
}

Token Scanner::nextToken() {
    if (currentChar >= fileContent.length())
        return Token(Token::END_OF_FILE, "EOF", "EOF", currentLine, currentRow);
    QChar firstChar = peek();
    while (firstChar.isSpace()) {
        advance();
        if (currentChar >= fileContent.length())
            return Token(Token::END_OF_FILE, "EOF", "EOF", currentLine, currentRow);
        firstChar = peek();
    }

    if (firstChar.isDigit())
        return parseNumberLiteral();
    else if (firstChar.isLetter() || firstChar == '_')
        return parseAlphaNum();
    else if (firstChar == '"')
        return parseStringLiteral();
    else if (firstChar == '\'')
        return parseCharLiteral();
    else if (firstChar == '/') {
        if (next() == '*' || next() == '/')
        {
            skipComment();
            return nextToken();
        }
        else throw MyException("Division unimplemented yet : '/' should only be used for comments");
    }
    else if (firstChar == '(') {
        auto l = currentLine;
        auto r = currentRow;
        advance();
        return Token(Token::LEFT_PAREN, "(", "(", l, r);
    }
    else if (firstChar == ')') {
        auto l = currentLine;
        auto r = currentRow;
        advance();
        return Token(Token::RIGHT_PARENT, ")", ")", l, r);
    }
    else if (firstChar == '{') {
        auto l = currentLine;
        auto r = currentRow;
        advance();
        return Token(Token::LEFT_BRACKET, "{", "{", l, r);
    }
    else if (firstChar == '}') {
        auto l = currentLine;
        auto r = currentRow;
        advance();
        return Token(Token::RIGHT_BRACKET, "}", "}", l, r);
    }
    else if (firstChar == '[') {
        auto l = currentLine;
        auto r = currentRow;
        advance();
        return Token(Token::LEFT_SQUARE_BRACKET, "[", "[", l, r);
    }
    else if (firstChar == ']') {
        auto l = currentLine;
        auto r = currentRow;
        advance();
        return Token(Token::RIGHT_SQUARE_BRACKET, "[", "]", l, r);
    }
    else if (firstChar == '<') {
        auto l = currentLine;
        auto r = currentRow;
        advance();
        if (peek() == '=') {
            advance();
            return Token(Token::LET, "<=", "<=", l, r);
        }
        else
            return Token(Token::LT, "<", "<", l, r);
    }
    else if (firstChar == '>') {
        auto l = currentLine;
        auto r = currentRow;
        advance();
        if (peek() == '=') {
            advance();
            return Token(Token::GET, ">=", ">=", l, r);
        }
        else
            return Token(Token::GT, ">", ">", l, r);
    }
    else if (firstChar == '=') {
        auto l = currentLine;
        auto r = currentRow;
        advance();
        if (peek() == '=') {
            advance();
            return Token(Token::EQ, "==", "==", l, r);
        }
        else
            return Token(Token::EQUAL, "=", "=", l, r);
    }
    else if (firstChar == '!') {
        auto l = currentLine;
        auto r = currentRow;
        advance();
        if (peek() == '=') {
            advance();
            return Token(Token::NEQ, "!=", "!=", l, r);
        }
        else
            return Token(Token::NOT, "!", "!", l, r);
    }
    else if (firstChar == ';') {
        auto l = currentLine;
        auto r = currentRow;
        advance();
        return Token(Token::SEMICOLON, ";", ";", l, r);
    }
    else if (firstChar == '-') {
        if (next() == '>') {
            auto l = currentLine;
            auto r = currentRow;
            advance(); advance(); return Token(Token::ARROW, "->", "->", l, r);
        }
        else {
            //TODO : implement -=
            auto l = currentLine;
            auto r = currentRow;
            advance();
            return Token(Token::MINUS, "-", "-", l, r);
        }
    }


    throw MyException(QString("Parse error... Line is %1, row is %2.").arg(currentLine).arg(currentRow));
}
