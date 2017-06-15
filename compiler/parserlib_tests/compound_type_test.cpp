#include "compound_type_test.h"
#include "type.h"
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

void CompoundTypeTest::structConversion() {
    /*  Checking for the equivalent of this code :
     * struct Rec {
     *  Int w;
     *  Int h;
     * };
     *
     * struct Point {
     *  Float x;
     *  Float y;
     * };
     *
     * struct Character {
     *  Point pos;
     *  Rec picture;
     * };
     * */

    CompoundType Int = CompoundType::Primitive("Int");
    CompoundType Float = CompoundType::Primitive("Float");

    QMap<QString, CompoundType> RecMap;
    RecMap["w"] = Int;
    RecMap["h"] = Int;
    CompoundType Rec = CompoundType::Struct("Rec", RecMap);

    QMap<QString, CompoundType> PointMap;
    PointMap["w"] = Float;
    PointMap["h"] = Float;
    CompoundType Point = CompoundType::Struct("Point", PointMap);

    QMap<QString, CompoundType> CharacterMap;
    CharacterMap["pos"] = Point;
    CharacterMap["picture"] = Rec;
    CompoundType Character = CompoundType::Struct("Character", CharacterMap);

    QVERIFY(Character.structValues()["pos"] == Point);


}

void CompoundTypeTest::valueEquality() {
    CompoundType Int = CompoundType::Primitive("Int");
    CompoundType Int2 = CompoundType::Primitive("Int");
    QVERIFY(Int == Int2);

    CompoundType Float = CompoundType::Primitive("Float");

    //Struct comparison
    QMap<QString, CompoundType> RecMap;
    RecMap["w"] = Int;
    RecMap["h"] = Int;
    CompoundType Rec = CompoundType::Struct("Rec", RecMap);
    RecMap["w"] = Float;
    CompoundType falseRec = CompoundType::Struct("Rec", RecMap);
    QVERIFY(Rec != falseRec);

    //Enum comparison
    QMap<QString, int> enumMap;
    enumMap["RED"] = 1;
    auto enum1 = CompoundType::Enum("Enum", enumMap);
    enumMap["RED"] = 2;
    auto enum2 = CompoundType::Enum("Enum", enumMap);
    QVERIFY(enum1 != enum2);

}
