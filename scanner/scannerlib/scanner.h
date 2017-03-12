#ifndef SCANNER_H
#define SCANNER_H

#include <QString>
#include <QChar>
#include <QVector>
#include <QSharedPointer>
#include <QJsonDocument>
#include "token.h"

/**
 * @class Scanner
 * @brief Class representing a scanner (lexical analyzer). It takes a file path as input and generates tokens, either lazily or as a QVector.
 */
class Scanner
{
public:

    static Scanner fromFile(const QString& path);
    static Scanner fromString(const QString& content);
    static Scanner fromJson(const QJsonDocument& sourceDoc);

    Scanner(Scanner &&src) = default;

    /**
     * @brief Accessor to the vector of tokens parsed at construction time.
     * @return const reference to the vector of tokens.
     */
    const QVector<Token>& tokens() const {return _tokens;}

    /**
     * @brief Accessor to a (const) JSonDocument storing all tokens as an array.
     * @return a shared pointer.
     */
    QSharedPointer<const QJsonDocument> JsonDoc();

private:
    //Private constructor from a file to tokenize OR the content.
    Scanner(const QString& pathOrContent, bool isPath);
    //Utility
    void doParse();
    //Private constructor
    Scanner(const QJsonDocument& sourceDoc);

    Scanner() = delete;
    Scanner(const Scanner& src) = delete;

    Scanner& operator= (const Scanner& src) = delete;
    Scanner& operator= (Scanner&& src) = delete;

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

    QSharedPointer<QJsonDocument> _doc;
};

#endif // SCANNER_H
