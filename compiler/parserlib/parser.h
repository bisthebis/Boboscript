#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include <QVector>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QtDebug>

class FileAST;

class Parser
{
    friend class ParserTest;

public:
    Parser(const QVector<Token>& tokens);
    const QString& getLog() const {
        return _log;
    }

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

    struct VariableDeclaration {
        QString type;
        QString name;
        static VariableDeclaration create(QString t, QString n) {
            VariableDeclaration vd;
            vd.type = t;
            vd.name = n;
            return vd;
        }
    };

    struct FunctionDefinition {
        QString name;
        QString returnType;
        QStringList argTypes;
        /*TODO : add instructions'AST*/
    };

    struct EnumDeclaration {
        QString name;
        QMap<QString, int> values;
    };

    struct ClassDeclaration {
        QString name;
        QVector<VariableDeclaration> members;
        QVector<FunctionDefinition> methods;
    };

    struct StructDeclaration {
        QString name;
        QVector<VariableDeclaration> members;
    };
    /* End of inner types */

private:
    void parse();
    bool accept(Token::Type t);
    void expect(Token::Type t, QString err);


    /*Utility functions, according to the grammar */
    QSharedPointer<ExportedSymbol> parseExportedSymbolInModuleDecl(); //Inside a module declaration

    /*Utility for functions to update known informations about parsed file*/
    void parseDeclarationAndAddIt();

    StructDeclaration parseStructDeclaration();
    EnumDeclaration parseEnumDeclaration();
    VariableDeclaration parseVariableDeclaration();


    const QVector<Token>& tokens;
    QVector<Token>::const_iterator it;
    QVector<Token>::const_iterator lastAccepted;
    const QVector<Token>::const_iterator end;
    bool atEnd() const {return it == end;}

    QString _log;
    QTextStream log;

    QScopedPointer<FileAST> ast;


};

#endif // PARSER_H
