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

    setModuleName(moduleName);
    log << "Module name found : " << moduleName << endl;

    // Step 2) get all the exported declarations (functions and types inside the module)
    expect(Token::LEFT_BRACKET, "Module declaration must start with a left bracket '{'");

    while (!accept(Token::RIGHT_BRACKET)) {
        auto newestSymbol = this->parseExportedSymbol();
        if (newestSymbol->isFunction)
            addExportedFunction(newestSymbol->name, newestSymbol->returnType, newestSymbol->argTypes);
        else
            addExportedType(newestSymbol->name);
        accept(Token::COMMA); //Facultative
    }

    // Step 3) Now that module has ended, we expect a semicolong and then parse every other statement
    expect(Token::SEMICOLON, "Module declaration : missing semicolon");

    while (!atEnd()) { //TODO
        parseDeclarationAndAddIt();
    }

}

QSharedPointer<Parser::ExportedSymbol> Parser::parseExportedSymbol() {
    expect(Token::IDENTIFIER, "All declarations in a module must start with an identifier");
    QString first = lastAccepted->value.toString();
    if (accept(Token::COMMA))
    {
        log << "Parsed an exported type whose name is " << first;
        return QSharedPointer<ExportedSymbol>(ExportedSymbol::type(first));
    }

    /*It's a function.
    Two forms are allowed :
    -ReturnType func(argType, argType1,...) ->
    -func(argType, argType2,...) -> ReturnType
    */
    if (accept(Token::IDENTIFIER)) {
        QString returnType = first;
        QString funcName = lastAccepted->value.toString();
        QStringList argTypes;
        expect(Token::LEFT_PAREN, "Function signature must contain parenthesis");
        while (!accept(Token::RIGHT_PAREN)) {
            expect(Token::IDENTIFIER, "Expected typename"); //TODO : allow compound type names (qualifiers etc)
            argTypes << lastAccepted->value.toString();
            accept(Token::COMMA); // At the moment, compound type names will be seen as two types and so 2 args. TODO : fix this
        }

        log << "Parsed a function declaration (exproted in module) with C-style syntax. Name : " << funcName << ". Return type : " << returnType << ". Args types : ";
        for (auto& t : argTypes)
            log << t <<';';
        log << endl;

        return QSharedPointer<ExportedSymbol>(ExportedSymbol::func(funcName, returnType, argTypes));
    }

    else if (accept(Token::LEFT_PAREN)) {
        QString& funcName = first;
        QStringList argTypes;
        while (!accept(Token::RIGHT_PAREN)) {
            expect(Token::IDENTIFIER, "Expected typename"); //TODO : allow compound type names (qualifiers etc)
            argTypes << lastAccepted->value.toString();
            accept(Token::COMMA); // At the moment, compound type names will be seen as two types and so 2 args. TODO : fix this
        }
        expect(Token::ARROW, "Function declarations that do not start with return type must be followed by an arrow.");
        expect(Token::IDENTIFIER, "Arrow must be followed by a type name");
        QString returnType = lastAccepted->value.toString();
        log << "Parsed a function declaration (exproted in module) with C-style syntax. Name : " << funcName << ". Return type : " << returnType << ". Args types : ";
                for (auto& t : argTypes)
                    log << t <<';';
        log << endl;
        return QSharedPointer<ExportedSymbol>(ExportedSymbol::func(funcName, returnType, argTypes));


    }

    //Else it's a type declaration
    log << "Parsed a type to export : " << first << endl;
    return QSharedPointer<ExportedSymbol>(ExportedSymbol::type(first));
}

void Parser::parseDeclarationAndAddIt() {
    if (accept(Token::STRUCT)) {
        parseStruct();
    }
    else {
        throw MyException("Unimplemented method called : Parser::parseDeclarationAndAddIt");
    }
}

void Parser::parseStruct() {
    expect(Token::IDENTIFIER, "Struct must have a single-word name");
    const QString name = lastAccepted->value.toString();
    log << "Parsing struct called " << name << endl;
    expect(Token::LEFT_BRACKET, "Expected bracket after a struct declaration");
    while (!accept(Token::RIGHT_BRACKET)) {
        parseVariableDeclaration();
    }
    expect(Token::SEMICOLON, "Struct definition must end with a ;");
}

void Parser::parseVariableDeclaration() {
    throw MyException("Unimplemented method called : Parser::parseVariableDeclaration");
}
