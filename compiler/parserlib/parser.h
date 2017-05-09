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
#include <QtDebug>

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

    struct StructDeclaration {
        QVector<VariableDeclaration> members;
    };

    /*Utility functions, according to the grammar */
    QSharedPointer<ExportedSymbol> parseExportedSymbol(); //Inside a module declaration

    /*Utility for functions to update known informations about parsed file*/
    void setModuleName(QString n) {qWarning() << "UNIMPLEMENTED METHOD CALLED : Parser::setModuleName. Arg : " << n;}
    void addExportedType(QString n) {qWarning() << "UNIMPLEMENTED METHOD CALLED : Parser::addExportedType. Arg : " << n;}
    void addExportedFunction(QString n, QString rt, QStringList args) {qWarning() << "UNIMPLEMENTED METHOD CALLED : Parser::addExportedFunction. Args : " << n << ';' << rt << ',' << args;}
    void parseDeclarationAndAddIt();

    StructDeclaration parseStructDeclaration();
    VariableDeclaration parseVariableDeclaration();


    const QVector<Token>& tokens;
    QVector<Token>::const_iterator it;
    QVector<Token>::const_iterator lastAccepted;
    const QVector<Token>::const_iterator end;
    bool atEnd() const {return it == end;}

    QScopedPointer<FileAST> ast;

    QString _log;
    QTextStream log;




};

#endif // PARSER_H
