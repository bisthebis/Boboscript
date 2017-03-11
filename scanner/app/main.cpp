#include <QtCore>
#include "token.h"
#include "scanner.h"
#include "myexception.h"
#include "command_line.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    try {

        if (argc < 2)
            throw MyException("Wrong argument count");

        for (int i = 1; i < argc; ++i)
        {
            QString path = argv[i];
            qDebug() << "Tokenizing file : " << path;
            tokenizeFile(path);
        }

    }
    catch (MyException& e) {
        qDebug() << "Exception occured : " << e.msg;
    }


    return 0;
}
