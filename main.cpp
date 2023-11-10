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
    g.printGrammar();
    cout << "--------------------------------------" << endl;
    g.printFirstSet();
    cout << "--------------------------------------" << endl;
    g.printFollowSets();

    g.printSelectSets();


    return 0;
}