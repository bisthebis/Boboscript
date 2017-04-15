#include "parser.h"
#include "myexception.h"
#include <QRegularExpression>

static const QRegularExpression moduleNamePattern("^([A-Z]|_|[0-9])+$");

Parser::Parser(const QVector<Token> &tokens) : tokens(tokens), it(tokens.begin()), end(tokens.end()), log(&_log)
{
    parse();
}

bool Parser::accept(Token::Type t) {
    if (it->type == t) {
        lastAccepted = it++;
        return true;
    }
    return false;
}

void Parser::expect(Token::Type t, QString err) {
    if (it->type == t) {
        lastAccepted = it++;
        return;
    }

    throw MyException(QString("Unexpected token type. Received %1. Expected type %2. Error : %3").arg(it->toString()).arg(Token::typeToString(t)).arg(err));
}

void Parser::parse() {
    // Step 1) get module name
    expect(Token::MODULE, "File must start with a Module declaration");
    expect(Token::IDENTIFIER, "'module' keyword must be followed by an identifier that will be the module name, in uppercase");
    const QString moduleName = lastAccepted->lexeme;
    if (!moduleNamePattern.match(moduleName).hasMatch())
        throw MyException(QString("Module name must contain only uppercase letters, digits and underscores. Thus, name %1 is incorrect").arg(moduleName));
    log << "Module name found : " << moduleName << endl;

    // Step 2) get all the exported declarations (functions and types inside the module)
    expect(Token::LEFT_BRACKET, "Module declaration must start with a left bracket '{'");

    // Step 3) as long as the module declaration hasn't ended, parse what is in it (type declarations

}
