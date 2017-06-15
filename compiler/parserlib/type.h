#ifndef TYPE_H
#define TYPE_H

#include <QString>
#include <QVariant>
#include <QMap>
#include "myexception.h"

/**
 * @brief Pseudo-immutable structure representing a compound type (struct, class, enum)
 */
class CompoundType {

public:
    enum Category {
        STRUCT,
        ENUM,
        CLASS,
        PRIMITIVE,
    };

    QString name() const { return _name;}
    Category category() const { return _type;}
    const QMap<QString, int>& enumValues() const {if (_type != Category::ENUM) throw  MyException("Tried to read enum values of non-enum type"); return _enum_content;}

    static CompoundType Enum(QString name, const QMap<QString, int>& values) {
        CompoundType result;
        result._type = Category::ENUM;
        result._name = name;
        result._enum_content = values;

        return result;
    }


private:
    Category _type;
    QString _name;
    QMap<QString, int> _enum_content; //For enum : QMap<QString, int>.

    //TODO : Struct should be Map of String/Type with Type being Compound or simple. Class are that OR Function.


};

#endif // TYPE_H
