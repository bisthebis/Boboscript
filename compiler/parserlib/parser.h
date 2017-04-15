#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "fileast.h"
#include <QVector>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QTextStream>
#include <QString>
#include <QStringList>

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

    /* Inner types */
    struct ExportedSymbol {
        static ExportedSymbol* type(QString n) {
            ExportedSymbol* r = new ExportedSymbol();
            r->name = n;
            r->isFunction = false;
            return r;
        }

        static ExportedSymbol* func(QString n, QString rt, QStringList args) {
            ExportedSymbol* r = new ExportedSymbol();
            r->name = n;
            r->isFunction = true;
            r->argTypes = args;
            r->returnType = rt;
            return r;
        }

        QString name;
        bool isFunction;
        QString returnType;
        QStringList argTypes;
    };

    /*Utility functions, according to the grammar */
    QSharedPointer<ExportedSymbol> parseExportedSymbol(); //Inside a module declaration



    const QVector<Token>& tokens;
    QVector<Token>::const_iterator it;
    QVector<Token>::const_iterator lastAccepted;
    const QVector<Token>::const_iterator end;

    QScopedPointer<FileAST> ast;

    QString _log;
    QTextStream log;




};

#endif // PARSER_H
