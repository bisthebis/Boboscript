#ifndef SCANNER_H
#define SCANNER_H

#include <QTextStream>
#include <QString>
#include <QFile>
#include "token.h"

/**
 * @class Scanner
 * @brief Class representing a scanner (lexical analyzer). It takes a file path as input and generates tokens, either lazily or as a QVector.
 */
class Scanner
{
public:
    Scanner();

private:
    QFile file;
    QTextStream stream;
    QVector<Token> tokens;
    int currentLine = 0;
    int currentRow = 0;
};

#endif // SCANNER_H
