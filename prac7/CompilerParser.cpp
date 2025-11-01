
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
    ParseTree* Ptree = new ParseTree("subroutine", "");
    Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "")->getValue())); // type of subroutine

    if (have("keyword", "void") || have("keyword", "int") || have("keyword", "char") ||
        have("keyword", "boolean"))
        Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "")->getValue()));
    else
        Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

    Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "(")->getValue()));
    Ptree->addChild(compileParameterList());
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ")")->getValue()));
    Ptree->addChild(compileSubroutineBody());
    return Ptree;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* Ptree = new ParseTree("parameterList", "");
    if (have("keyword", "int") || have("keyword", "char") || have("keyword", "boolean") || have("identifier", "")) {
        if (have("keyword", "")) Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "")->getValue()));
        else Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
        Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

        while (have("symbol", ",")) {
            Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ",")->getValue()));
            if (have("keyword", "")) Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "")->getValue()));
            else Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
            Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
        }
    }
    return Ptree;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* Ptree = new ParseTree("subroutineBody", "");
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "{")->getValue()));

    while (have("keyword", "var")) Ptree->addChild(compileVarDec());
    Ptree->addChild(compileStatements());
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "}")->getValue()));
    return Ptree;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* Ptree = new ParseTree("varDec", "");
    Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "var")->getValue()));

    if (have("keyword", "")) Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "")->getValue()));
    else Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

    Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

    while (have("symbol", ",")) {
        Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ",")->getValue()));
        Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
    }

    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ";")->getValue()));
    return Ptree;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    ParseTree* Ptree = new ParseTree("statements", "");

    while (have("keyword", "let") || have("keyword", "do") ||
           have("keyword", "return") || have("keyword", "if") ||
           have("keyword", "while")) {

        if (have("keyword", "let"))       Ptree->addChild(compileLet());
        else if (have("keyword", "do"))   Ptree->addChild(compileDo());
        else if (have("keyword", "return")) Ptree->addChild(compileReturn());
        else if (have("keyword", "if"))   Ptree->addChild(compileIf());
        else if (have("keyword", "while"))Ptree->addChild(compileWhile());
        else break;
    }

    return Ptree;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    ParseTree* Ptree = new ParseTree("letStatement", "");
    Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "let")->getValue()));
    Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

    if (have("symbol", "[")) {
        Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "[")->getValue()));
        Ptree->addChild(compileExpression());
        Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "]")->getValue()));
    }

    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "=")->getValue()));
    Ptree->addChild(compileExpression());
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ";")->getValue()));
    return Ptree;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    ParseTree* Ptree = new ParseTree("ifStatement", "");
    Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "if")->getValue()));
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "(")->getValue()));
    Ptree->addChild(compileExpression());
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ")")->getValue()));

    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "{")->getValue()));
    Ptree->addChild(compileStatements());
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "}")->getValue()));

    if (have("keyword", "else")) {
        Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "else")->getValue()));
        Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "{")->getValue()));
        Ptree->addChild(compileStatements());
        Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "}")->getValue()));
    }
    return Ptree;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    ParseTree* Ptree = new ParseTree("whileStatement", "");
    Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "while")->getValue()));
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "(")->getValue()));
    Ptree->addChild(compileExpression());
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ")")->getValue()));
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "{")->getValue()));
    Ptree->addChild(compileStatements());
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "}")->getValue()));
    return Ptree;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    ParseTree* Ptree = new ParseTree("doStatement", "");
    Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "do")->getValue()));
    Ptree->addChild(compileExpression());
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ";")->getValue()));
    return Ptree;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    ParseTree* Ptree = new ParseTree("returnStatement", "");
    Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "return")->getValue()));
    if (!have("symbol", ";"))
        Ptree->addChild(compileExpression());
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ";")->getValue()));
    return Ptree;
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
