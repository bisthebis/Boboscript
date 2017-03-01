#include "token.h"

Token::Token(Type t, QString lexeme, QVariant value, int line, int column) : type(t), lexeme(lexeme), value(value)
{
    location.line = line;
    location.column = column;
}
