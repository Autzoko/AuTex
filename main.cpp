//
// Created by llt02 on 10/23/2023.
//
#include "include/lexer/lexer.h"
#include "include/parser/Grammar.h"
#include "include/parser/Parser.h"
#include "include/parser/Operator.h"

int main()
{
    //lexer lex("../test/source/test.ax", "../test/target/_out.tgt");
    //lex.lex(false);
    //lex.generate();

    Grammar g = Grammar("../test/source/opr.gr");
    g.printInformation();

    //Parser parser = Parser(g);
    //parser.emit("i=(i+i)");
    //parser.printLog();

    //RecursiveDescentParser rdp;
    //rdp.emit("whlie i + i do i = i / i + i");

    OperatorGrammar operatorGrammar = OperatorGrammar(g);
    operatorGrammar.emit();
    operatorGrammar.printInfo();

    OperatorPrecedentParser operatorPrecedentParser = OperatorPrecedentParser(operatorGrammar);
    operatorPrecedentParser.emit("i*(i+i)");
    operatorPrecedentParser.printLog();


    //still has bugs when add "(" and ")"

    return 0;
}