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
    void pushExportedType(const Parser::ExportedSymbol& s) {exportedTypes.append(s);}
    void pushExportedFunction(const Parser::ExportedSymbol& s) {exportedFunctions.append(s);}
    void pushStructure(const Parser::StructDeclaration& s) {structures[s.name] = s;}

private:
    QString moduleName;
    QVector<Parser::ExportedSymbol> exportedTypes;
    QVector<Parser::ExportedSymbol> exportedFunctions;
    QMap<QString, Parser::StructDeclaration> structures;

};

#endif // FILEAST_H
