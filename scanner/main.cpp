#include <QtCore>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTimer::singleShot(1000, [&](){qDebug() << "Leaving..."; a.exit();});

    return a.exec();
}
