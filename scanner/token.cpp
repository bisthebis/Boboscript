#include "token.h"
#include "myexception.h"

Token::Token(Type t, QString lexeme, QVariant value, int line, int column) : type(t), lexeme(lexeme), value(value) {
    location.line = line;
    location.column = column;
}

QString Token::typeToString(Type t) {
#define ADD_CASE(type) case(type): return #type;

    switch (t) {
    ADD_CASE(END_OF_FILE);
    ADD_CASE(IDENTIFIER);
    ADD_CASE(STR_LIT);
    ADD_CASE(CHAR_LIT);
    ADD_CASE(INT_LIT);
    ADD_CASE(DOUBLE_LIT);
    ADD_CASE(BOOL_LIT);
    ADD_CASE(COMMA);
    ADD_CASE(SEMICOLON);
    ADD_CASE(DOT);
    ADD_CASE(ARROW);
    ADD_CASE(LEFT_PAREN);
    ADD_CASE(RIGHT_PARENT);
    ADD_CASE(LEFT_BRACKET);
    ADD_CASE(RIGHT_BRACKET);
    ADD_CASE(LEFT_SQUARE_BRACKET);
    ADD_CASE(RIGHT_SQUARE_BRACKET);
    ADD_CASE(IF);
    ADD_CASE(ELSE);
    ADD_CASE(ELSEIF);
    ADD_CASE(WHILE);
    ADD_CASE(FOR);
    ADD_CASE(DO);
    ADD_CASE(RETURN);
    ADD_CASE(FUNCTION);
    ADD_CASE(MODULE);
    ADD_CASE(NEW);
    ADD_CASE(STRUCT);
    ADD_CASE(CLASS);
    ADD_CASE(ENUM);
    ADD_CASE(NULL_LIT);
    ADD_CASE(CONST);
    ADD_CASE(FINAL);
    ADD_CASE(PUBLIC);
    ADD_CASE(PRIVATE);
    ADD_CASE(PROTECTED);
    ADD_CASE(PLUS);
    ADD_CASE(MINUS);
    ADD_CASE(TIMES);
    ADD_CASE(DIVISION);
    ADD_CASE(MODULO);
    ADD_CASE(UNARY_PLUS);
    ADD_CASE(UNARY_MINUS);
    ADD_CASE(EQUAL);
    ADD_CASE(EQ);
    ADD_CASE(GET);
    ADD_CASE(GT);
    ADD_CASE(LT);
    ADD_CASE(LET);
    ADD_CASE(NEQ);
    ADD_CASE(AND);
    ADD_CASE(OR);
    ADD_CASE(NOT);
    ADD_CASE(PLUS_EQ);
    ADD_CASE(MINUS_EQ);
    ADD_CASE(TIMES_EQ);
    ADD_CASE(DIVISION_EQ);
    ADD_CASE(MODULO_EQ);
    default:
        throw MyException(QString("Couldn't stringify Token::Type. Type ID is %1").arg(t));
        break;
    }

#undef ADD_CASE
}

QString Token::toString() const {
    return QString("(%1, %2, %3, %4)")
            .arg(typeToString(type))
            .arg(lexeme)
            .arg(location.line)
            .arg(location.column);
}
