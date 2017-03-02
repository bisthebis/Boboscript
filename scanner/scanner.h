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
    QChar peek() const;
    QChar next();

    QString fileContent;
    QVector<Token> tokens;
    int currentChar = 0;
    int currentLine = 0;
    int currentRow = 0;
};

#endif // SCANNER_H
