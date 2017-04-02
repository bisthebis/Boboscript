#include "parser.h"
#include "myexception.h"

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
    const QString moduleName = lastAccepted->lexeme;
    log << "Module name found : " << moduleName << endl;

}
