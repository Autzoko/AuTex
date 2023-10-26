//
// Created by llt02 on 10/23/2023.
//
#include "include/lexer/lexer.h"

int main()
{
    lexer lex("../test/source/test.ax", "../test/target/_out.tgt");
    lex.lex(false);
    lex.generate();
    return 0;
}