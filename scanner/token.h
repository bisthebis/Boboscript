#ifndef TOKEN_H
#define TOKEN_H

#include <QVariant>
#include <QJsonObject>
#include <QString>

/**
 * @brief Container for a Token object
 */
struct Token
{
    enum Type {
        END_OF_FILE,
        IDENTIFIER,

        STR_LIT,
        CHAR_LIT,
        INT_LIT,
        DOUBLE_LIT,
        BOOL_LIT,

        COMMA,
        SEMICOLON,
        DOT,
        ARROW, // "->"

        LEFT_PAREN,
        RIGHT_PARENT,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        LEFT_SQUARE_BRACKET,
        RIGHT_SQUARE_BRACKET,

        IF,
        ELSE,
        ELSEIF,
        WHILE,
        FOR,
        DO,
        RETURN,
        FUNCTION,
        MODULE,
        NEW,
        STRUCT,
        CLASS,
        ENUM,
        NULL_LIT, //can't be called NULL for preprocessing reasons

        CONST,
        FINAL,
        PUBLIC,
        PRIVATE,
        PROTECTED,

        PLUS,
        MINUS,
        TIMES,
        DIVISION,
        MODULO,

        //Arithmetic assignment (+=, *= etc)
        PLUS_EQ,
        MINUS_EQ,
        TIMES_EQ,
        DIVISION_EQ,
        MODULO_EQ,

        //Comparison
        EQUAL, //Asignement
        EQ, // ==
        GET, // >=
        GT,
        LT,
        LET,
        NEQ, //!=

        //Logical operators
        AND, //&&
        OR, // ||
        NOT, // !


        //Others to be added later

    };

public:
    /**
      * @brief Default constructor only exist for the purpose of containers. It should not be manually used
      */
    Token() = default;

    /**
     * @brief Construct a token with the given values.
     * @param type
     * @param lexeme
     * @param value
     * @param line
     * @param column
     */
    Token(Type type, QString lexeme, QVariant value, int line, int column);

    /**
     * @brief Returns a string containing every informations, including stringified type
     * @return "(type, lexeme, line, column)"
     */
    QString toString() const;

    /**
     * @brief Returns a QJSonObject containing token data
     * @return a QJsonObject
     */
    QJsonObject toJsonObject() const;

    /**
     * @brief returns the stringified version of Token::Type. RETURN becomes "RETURN" etc.
     * @param type to convert
     * @return
     */
    static QString typeToString(Type t);

    /**
     * @brief Type of the token.
     */
    Type type;
    /**
     * @brief String consumed to produce this token.
     */
    QString lexeme;
    /**
     * @brief Value of the token. If it is a literal (number, bool, char, string),
     * then it contains that value, otherwise it's the lexeme.
     */
    QVariant value;

    /**
     * @brief sub-structure containing the line and column where the token begins.
     */
    struct {
        int line;
        int column;
    } location;


};

#endif // TOKEN_H
