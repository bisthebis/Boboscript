#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "fileast.h"
#include <QVector>
#include <QScopedPointer>
#include <QTextStream>
#include <QString>

class Parser
{
public:
    Parser(const QVector<Token>& tokens);
    const QString& getLog() const {
        return _log;
    }

private:
    void parse();
    bool accept(Token::Type t);
    void expect(Token::Type t, QString err);

    const QVector<Token>& tokens;
    QVector<Token>::const_iterator it;
    QVector<Token>::const_iterator lastAccepted;
    const QVector<Token>::const_iterator end;

    QScopedPointer<FileAST> ast;

    QString _log;
    QTextStream log;

};

#endif // PARSER_H
