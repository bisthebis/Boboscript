#include <QtCore>
#include "token.h"
#include "scanner.h"
#include "myexception.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    try {
        QString targetFile;
        if (argc == 2)
            targetFile = a.arguments().at(1);
        else
            throw MyException("Wrong argument count");
        Scanner scan(targetFile);

        while (true) {
            auto t = scan.nextToken();
            if (t.type == Token::END_OF_FILE)
                break;
            qDebug() << t.toString();
        }
    }
    catch (MyException& e) {
        qDebug() << "Exception occured : " << e.msg;
    }


    return 0;
}
