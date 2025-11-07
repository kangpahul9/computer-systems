
#include "CompilerParser.h"

/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */

CompilerParser::CompilerParser(std::list<Token *> tokens)
{
    allTokens = tokens;
    currToken = allTokens.begin();
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree *CompilerParser::compileProgram()
{
    return compileClass();
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree *CompilerParser::compileClass()
{
    ParseTree *Ptree = new ParseTree("class", "");
    Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "class")->getValue()));
    Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "{")->getValue()));

    while (have("keyword", "static") || have("keyword", "field"))
    {
        Ptree->addChild(compileClassVarDec());
    }
    while (have("keyword", "constructor") || have("keyword", "method") || have("keyword", "function"))
    {
        Ptree->addChild(compileSubroutine());
    }

    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "}")->getValue()));

    return Ptree;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree *CompilerParser::compileClassVarDec()
{
    ParseTree *Ptree = new ParseTree("classVarDec", "");
    Ptree->addChild(new ParseTree("keyword", mustBe("keyword", have("keyword", "static") ? "static" : "field")->getValue()));
    if (have("keyword", "")) {
    Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "")->getValue()));
} else {
    Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
}

    Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

    while (have("symbol", ","))
    {
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
ParseTree *CompilerParser::compileSubroutine()
{
    ParseTree* Ptree = new ParseTree("subroutine", "");
    if (have("keyword", "constructor"))
        Ptree->addChild(mustBe("keyword", "constructor"));
    else if (have("keyword", "method"))
        Ptree->addChild(mustBe("keyword", "method"));
    else
        Ptree->addChild(mustBe("keyword", "function"));
    if (have("keyword", "void"))
        Ptree->addChild(mustBe("keyword", "void"));
    else if (have("keyword", "int") || have("keyword", "char") || have("keyword", "boolean"))
        Ptree->addChild(mustBe("keyword", ""));
    else
        Ptree->addChild(mustBe("identifier", ""));
    Ptree->addChild(mustBe("identifier", ""));
    Ptree->addChild(mustBe("symbol", "("));
    Ptree->addChild(compileParameterList());
    Ptree->addChild(mustBe("symbol", ")"));
    Ptree->addChild(compileSubroutineBody());
    return Ptree;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree *CompilerParser::compileParameterList()
{
    ParseTree *Ptree = new ParseTree("parameterList", "");
    if (have("keyword", "int") || have("keyword", "char") || have("keyword", "boolean") || have("identifier", ""))
    {
        if (have("keyword", ""))
            Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "")->getValue()));
        else
            Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
        Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

        while (have("symbol", ","))
        {
            Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ",")->getValue()));
            if (have("keyword", ""))
                Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "")->getValue()));
            else
                Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
            Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
        }
    }
    return Ptree;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree *CompilerParser::compileSubroutineBody()
{
    ParseTree *Ptree = new ParseTree("subroutineBody", "");

    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "{")->getValue()));

    while (have("keyword", "var"))
        Ptree->addChild(compileVarDec());

    Ptree->addChild(compileStatements());

    Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "}")->getValue()));

    return Ptree;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree *CompilerParser::compileVarDec()
{
    ParseTree *Ptree = new ParseTree("varDec", "");
    Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "var")->getValue()));

    if (have("keyword", ""))
        Ptree->addChild(new ParseTree("keyword", mustBe("keyword", "")->getValue()));
    else
        Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

    Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));

    while (have("symbol", ","))
    {
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
ParseTree *CompilerParser::compileStatements()
{
    ParseTree* Ptree = new ParseTree("statements", "");

    while (have("keyword", "let") || have("keyword", "if") ||
           have("keyword", "while") || have("keyword", "do") ||
           have("keyword", "return")) {

        if (have("keyword", "let")) {
            Ptree->addChild(compileLet());
        } else if (have("keyword", "if")) {
            Ptree->addChild(compileIf());
        } else if (have("keyword", "while")) {
            Ptree->addChild(compileWhile());
        } else if (have("keyword", "do")) {
            Ptree->addChild(compileDo());
        } else if (have("keyword", "return")) {
            Ptree->addChild(compileReturn());
        }
    }

    return Ptree;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree *CompilerParser::compileLet()
{
    ParseTree* Ptree = new ParseTree("letStatement", "");
    Ptree->addChild(mustBe("keyword", "let"));
    Ptree->addChild(mustBe("identifier", ""));
    if (have("symbol", "[")) {
        Ptree->addChild(mustBe("symbol", "["));
        Ptree->addChild(compileExpression());
        Ptree->addChild(mustBe("symbol", "]"));
    }
    Ptree->addChild(mustBe("symbol", "="));
    Ptree->addChild(compileExpression());
    Ptree->addChild(mustBe("symbol", ";"));
    return Ptree;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree *CompilerParser::compileIf()
{
    ParseTree* Ptree = new ParseTree("ifStatement", "");
    Ptree->addChild(mustBe("keyword", "if"));
    Ptree->addChild(mustBe("symbol", "("));
    Ptree->addChild(compileExpression());
    Ptree->addChild(mustBe("symbol", ")"));
    Ptree->addChild(mustBe("symbol", "{"));
    Ptree->addChild(compileStatements());
    Ptree->addChild(mustBe("symbol", "}"));
    if (have("keyword", "else")) {
        Ptree->addChild(mustBe("keyword", "else"));
        Ptree->addChild(mustBe("symbol", "{"));
        Ptree->addChild(compileStatements());
        Ptree->addChild(mustBe("symbol", "}"));
    }
    return Ptree;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree *CompilerParser::compileWhile()
{
    ParseTree* Ptree = new ParseTree("whileStatement", "");
    Ptree->addChild(mustBe("keyword", "while"));
    Ptree->addChild(mustBe("symbol", "("));
    Ptree->addChild(compileExpression());
    Ptree->addChild(mustBe("symbol", ")"));
    Ptree->addChild(mustBe("symbol", "{"));
    Ptree->addChild(compileStatements());
    Ptree->addChild(mustBe("symbol", "}"));
    return Ptree;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree *CompilerParser::compileDo()
{
    ParseTree* Ptree = new ParseTree("doStatement", "");
    Ptree->addChild(mustBe("keyword", "do"));
    Ptree->addChild(compileExpression());
    Ptree->addChild(mustBe("symbol", ";"));
    return Ptree;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree *CompilerParser::compileReturn()
{
    ParseTree* ptree = new ParseTree("returnStatement", "");
    ptree->addChild(mustBe("keyword", "return"));
    if (!have("symbol", ";")) {
        ptree->addChild(compileExpression());
    }
    ptree->addChild(mustBe("symbol", ";"));
    return ptree;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree *CompilerParser::compileExpression()
{
    ParseTree* Ptree = new ParseTree("expression", "");
    Ptree->addChild(compileTerm());

    bool isOperator = (
        have("symbol", "+") || have("symbol", "-") ||
        have("symbol", "*") || have("symbol", "/") ||
        have("symbol", "&") || have("symbol", "|") ||
        have("symbol", "<") || have("symbol", ">") ||
        have("symbol", "=")
    );

    while (isOperator) {
        Ptree->addChild(mustBe("symbol", "")); 
        Ptree->addChild(compileTerm());        
        isOperator = (
            have("symbol", "+") || have("symbol", "-") ||
            have("symbol", "*") || have("symbol", "/") ||
            have("symbol", "&") || have("symbol", "|") ||
            have("symbol", "<") || have("symbol", ">") ||
            have("symbol", "=")
        );
    }

    return Ptree;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree *CompilerParser::compileTerm()
{
    ParseTree *Ptree = new ParseTree("term", "");
    Token *tok = current();
    if (!tok)
        throw ParseException();
    if (tok->getType() == "integerConstant")
    {
        Ptree->addChild(new ParseTree("integerConstant", mustBe("integerConstant", "")->getValue()));
        return Ptree;
    }
    if (tok->getType() == "stringConstant")
    {
        Ptree->addChild(new ParseTree("stringConstant", mustBe("stringConstant", "")->getValue()));
        return Ptree;
    }
    if (tok->getType() == "keyword" &&
        (tok->getValue() == "true" || tok->getValue() == "false" ||
         tok->getValue() == "null" || tok->getValue() == "this"))
    {
        Ptree->addChild(new ParseTree("keyword", mustBe("keyword", tok->getValue())->getValue()));
        return Ptree;
    }
    if (have("symbol", "("))
    {
        Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "(")->getValue()));
        Ptree->addChild(compileExpression());
        Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ")")->getValue()));
        return Ptree;
    }
    if (have("symbol", "-") || have("symbol", "~"))
    {
        Ptree->addChild(new ParseTree("symbol", mustBe("symbol", tok->getValue())->getValue()));
        Ptree->addChild(compileTerm());
        return Ptree;
    }
    if (have("identifier", ""))
    {
        std::string name = mustBe("identifier", "")->getValue();

        if (have("symbol", "["))
        {
            Ptree->addChild(new ParseTree("identifier", name));
            Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "[")->getValue()));
            Ptree->addChild(compileExpression());
            Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "]")->getValue()));
            return Ptree;
        }

        if (have("symbol", "(") || have("symbol", "."))
        {
            Ptree->addChild(new ParseTree("identifier", name));
            if (have("symbol", "."))
            {
                Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ".")->getValue()));
                Ptree->addChild(new ParseTree("identifier", mustBe("identifier", "")->getValue()));
            }
            Ptree->addChild(new ParseTree("symbol", mustBe("symbol", "(")->getValue()));
            Ptree->addChild(compileExpressionList());
            Ptree->addChild(new ParseTree("symbol", mustBe("symbol", ")")->getValue()));
            return Ptree;
        }

        Ptree->addChild(new ParseTree("identifier", name));
        return Ptree;
    }

    throw ParseException();
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree *CompilerParser::compileExpressionList()
{
    ParseTree* Ptree = new ParseTree("expressionList", "");
    if (!have("symbol", ")")) {
        Ptree->addChild(compileExpression());
        while (have("symbol", ",")) {
            Ptree->addChild(mustBe("symbol", ","));
            Ptree->addChild(compileExpression());
        }
    }
    return Ptree;
}

/**
 * Advance to the next token
 */
void CompilerParser::next()
{
    if (currToken != allTokens.end())
    {
        ++currToken;
    }
}

/**
 * Return the current token
 * @return the Token
 */
Token *CompilerParser::current()
{
    if (currToken == allTokens.end())
    {
        return nullptr;
    }
    return *currToken;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue)
{
    Token *tok = current();
    if (!tok)
        return false;
    bool matchTypes = (expectedType == "" || tok->getType() == expectedType);
    bool matchValues = (expectedValue == "" || tok->getValue() == expectedValue);
    return matchTypes && matchValues;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token *CompilerParser::mustBe(std::string expectedType, std::string expectedValue)
{
    Token *tok = current();
    if (!tok)
        throw ParseException();

    if (tok->getType() == expectedType && (expectedValue == "" || tok->getValue() == expectedValue))
    {
        next();
        return tok;
    }
    else
    {
        throw ParseException();
    }
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char *ParseException::what()
{
    return "An Exception occurred while parsing!";
}
