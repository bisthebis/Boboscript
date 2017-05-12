#ifndef FILEAST_H
#define FILEAST_H

#include <QString>
#include <QVector>
#include <QMap>
#include "parser.h"

class FileAST
{
public:
    FileAST();
    void setName(QString n) {moduleName = n;}
    void pushExportedSymbol(const Parser::ExportedSymbol& s) {exportedSymbols.append(s);}
    void pushStructure(const Parser::StructDeclaration& s) {structures[s.name] = s;}

private:
    QString moduleName;
    QVector<Parser::ExportedSymbol> exportedSymbols;
    QMap<QString, Parser::StructDeclaration> structures;

};

#endif // FILEAST_H
