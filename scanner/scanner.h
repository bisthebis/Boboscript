#ifndef SCANNER_H
#define SCANNER_H

#include <QString>
#include <QChar>
#include <QVector>
#include "token.h"

/**
 * @class Scanner
 * @brief Class representing a scanner (lexical analyzer). It takes a file path as input and generates tokens, either lazily or as a QVector.
 */
class Scanner
{
public:
    Scanner(const QString& sourcePath);
    /**
     * @brief Read until a token is parsed, add it to the vector of tokens and return the last one (by value).
     * @return the newest token.
     */
    Token nextToken();

private:
    QChar peek() const; //Current character
    QChar next() const; //Read next character
    void advance();

    //Utility functions for nextToken().
    Token parseAlphaNum(); //Parse an expression that starts with a letter : identifiers, reserved words, bool literals
    Token parseStringLiteral();
    Token parseCharLiteral();
    Token parseNumberLiteral();
    void skipComment();

    QString fileContent;
    QVector<Token> tokens;
    int currentChar = 0;
    int currentLine = 1;
    int currentRow = 1;
};

#endif // SCANNER_H
