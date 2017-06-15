#include "compound_type_test.h"
#include "compound_type.h"
#include <QMap>
#include <QString>
#include <QtTest/QtTest>

CompoundTypeTest::CompoundTypeTest()
{

}


void CompoundTypeTest::enumConversion() {
    //Checking for the equivalent of "enum Color {RED = 1, BLUE = 5, GREEN = 3};"
    QMap<QString, int> values;
    values["RED"] = 1;
    values["BLUE"] = 5;
    values["GREEN"] = 3;

    CompoundType type = CompoundType::Enum("Color", values);
    QVERIFY(type.name() == "Color");
    const auto valuesEnd = values.cend();
    for (auto it = values.cbegin(); it != valuesEnd; ++it) {
        QVERIFY(*it == type.enumValues()[it.key()]);
    }
}
