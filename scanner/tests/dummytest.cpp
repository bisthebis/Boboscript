#include <QtCore>
#include <QtTest/QtTest>

class DummyTest : public QObject {
    Q_OBJECT
private slots:
    void succeed();
};

void DummyTest::succeed() {
    QVERIFY(true);
}

QTEST_MAIN(DummyTest)
#include "dummytest.moc"
