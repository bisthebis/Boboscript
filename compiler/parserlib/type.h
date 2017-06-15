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


    bool operator==(const CompoundType& other) const {
        if ((_type != other._type) || (_name != other._name))
            return false;

        if (_type == Category::PRIMITIVE)
            return true;

        if (_type == Category::ENUM)
        {
            if (_enum_content.size() != other._enum_content.size())
                return false;

            auto end = enumValues().cend();
            const auto& otherValues = other._enum_content;
            auto otherEnd = otherValues.cend();
            for (auto it = enumValues().cbegin(); it != end; ++it)
            {
                auto counterpart = otherValues.find(it.key());
                if (counterpart == otherEnd || *counterpart != *it)
                    return false;
            }

            return true;
        }


        if (_type == Category::STRUCT)
        {
            if (_struct_content.size() != other._struct_content.size())
                return false;

            auto end = structValues().cend();
            const auto& otherValues = other._struct_content;
            auto otherEnd = otherValues.cend();
            for (auto it = structValues().cbegin(); it != end; ++it)
            {
                auto counterpart = otherValues.find(it.key());
                if (counterpart == otherEnd || *counterpart != *it)
                    return false;
            }

            return true;
        }

        throw MyException("Unimplemented comparison for non-primitive types");
    }
    bool operator !=(const CompoundType& other) const {
        return !(*this == other);
    }

    QString name() const { return _name;}
    Category category() const { return _type;}
    const QMap<QString, int>& enumValues() const {if (_type != Category::ENUM) throw  MyException("Tried to read enum values of non-enum type"); return _enum_content;}
    const QMap<QString, CompoundType>& structValues() const {if (_type != Category::STRUCT) throw  MyException("Tried to read struct values of non-struct type"); return _struct_content;}

    static CompoundType Primitive(QString name) {
        CompoundType result;
        result._type = Category::PRIMITIVE;
        result._name = name;
        return result;
    }

    static CompoundType Enum(QString name, const QMap<QString, int>& values) {
        CompoundType result;
        result._type = Category::ENUM;
        result._name = name;
        result._enum_content = values;

        return result;
    }

    static CompoundType Struct(QString name, const QMap<QString, CompoundType>& values) {
        CompoundType result;
        result._type = Category::STRUCT;
        result._name = name;
        result._struct_content = values;

        return result;
    }





private:
    Category _type;
    QString _name;
    QMap<QString, int> _enum_content; //For enum : QMap<QString, int>.
    QMap<QString, CompoundType> _struct_content;
    //TODO : Struct should be Map of String/Type with Type being Compound or simple. Class are that OR Function.


};

#endif // TYPE_H
