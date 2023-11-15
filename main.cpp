//
// Created by llt02 on 10/23/2023.
//
#include "include/lexer/lexer.h"
#include "include/parser/Grammar.h"
#include "include/parser/Parser.h"

int main()
{
    //lexer lex("../test/source/test.ax", "../test/target/_out.tgt");
    //lex.lex(false);
    //lex.generate();

    Grammar g = Grammar("../test/source/test.gr");
    g.printInformation();

    Parser parser = Parser(g);
    parser.emit("i=(i+i)*i");
    parser.printLog();

    return 0;
}