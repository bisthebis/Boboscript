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
    Scanner() = delete;
    Scanner(const Scanner& src) = delete;
    Scanner(Scanner &&src) = delete;
    Scanner& operator= (const Scanner& src) = delete;
    Scanner& operator= (Scanner&& src) = delete;

    /**
     * @brief Accessor to the vecotr of tokens parsed at construction time.
     * @return const reference to the vector of tokens.
     */
    const QVector<Token>& tokens() const {return _tokens;}

private:
    QChar peek() const; //Current character
    QChar next() const; //Read next character
    void advance();

    Token nextToken();

    //Utility functions for nextToken().
    Token parseAlphaNum(); //Parse an expression that starts with a letter : identifiers, reserved words, bool literals
    Token parseStringLiteral();
    Token parseCharLiteral();
    Token parseNumberLiteral();
    void skipComment();

    QString fileContent;
    QVector<Token> _tokens;
    int currentChar = 0;
    int currentLine = 1;
    int currentRow = 1;
};

#endif // SCANNER_H
