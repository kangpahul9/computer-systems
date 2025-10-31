#include "CompilerParser.h"
std::list<Token*> allTokens;
std::list<Token*>::iterator currToken;
/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */

CompilerParser::CompilerParser(std::list<Token*> tokens) {
    allTokens = tokens;
    currToken = allTokens.begin();
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    if (!have("keyword", "class")) {
        throw ParseException();
    }
    return compileClass();
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    ParseTree* Ptree = new ParseTree("class", "");
    Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "class")->getValue()));
    Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "{")->getValue()));

    while(have("keyword", "static") || have("keyword", "field")){
        Ptree->addChild(compileClassVarDec());
    }
    while(have("keyword", "constructor") || have("keyword", "method") || have("keyword", "function")){
        Ptree->addChild(compileSubroutine());
    }

    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "}")->getValue()));

    return Ptree;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
   ParseTree* Ptree = new ParseTree("classVarDec", "");
    Ptree->addChild(new ParseTree("keyword", mustBe("keyword", have("keyword", "static") ? "static" : "field")->getValue()));
    Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "")->getValue())); // type keyword or identifier

    Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

    // Handle comma-separated variable names
    while (have("symbol", ",")) {
        Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ",")->getValue()));
        Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
    }

    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ";")->getValue()));
    return Ptree;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    return NULL;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    return NULL;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    return NULL;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    return NULL;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    return NULL;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    return NULL;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    return NULL;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    return NULL;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    if (currToken != allTokens.end()) {
        ++currToken;
    }
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    if (currToken == allTokens.end()) {
        return nullptr;
    }
    return *currToken;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    Token* tok = current();
    if (!tok) return false;
    if(tok->getType() != expectedType){
        return false;
    }
    if(expectedValue == ""){
        return true;
    }
    return tok->getValue() == expectedValue;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    Token* tok = current();
    if(tok->getType() == expectedType && (expectedValue == "" || tok->getValue() == expectedValue)) {
    next();
    return tok;
    } else {
    throw ParseException();
    }
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
