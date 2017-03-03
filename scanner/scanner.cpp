#include "scanner.h"
#include "myexception.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>

Scanner::Scanner(const QString& sourcePath) {
    QFile file(sourcePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw MyException(QString("Couldn't not open file %1. Error is : %2.").arg(sourcePath).arg(file.errorString()));

    QTextStream stream(&file);
    fileContent = stream.readAll();
}

QChar Scanner::peek() const {
    return fileContent.at(currentChar);
}

QChar Scanner::next() const {
    return fileContent.at(currentChar + 1);
}

void Scanner::advance() {

    ++currentChar;
    if (currentChar >= fileContent.length())
        throw MyException("End of file reached");
    if (result == QChar::LineFeed || result == QChar::LineSeparator)
    {
        ++currentLine;
        currentRow = 0;
    }
    else
    {
        ++currentRow;
    }
}

Token Scanner::nextToken()
{

}
