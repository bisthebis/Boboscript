#include "command_line.h"

#include "myexception.h"
#include "scanner.h"
#include <QtCore>

void tokenizeFile(const QString &path) {
    static const QRegularExpression sourceFile("^.*\\.bs$");
    if (!sourceFile.match(path).hasMatch())
        throw MyException(QString("Tried to compile a Boboscript file that hasn't extension .bs. Path is %1.").arg(path));

    QString outputFile = path;
    outputFile.chop(3);
    outputFile += "_tokens.json";

    auto scanner = Scanner::fromFile(path);

    auto data = scanner.JsonDoc()->toJson();
    QFile file(outputFile);
    file.open(QIODevice::WriteOnly);
    file.write(data);

}
