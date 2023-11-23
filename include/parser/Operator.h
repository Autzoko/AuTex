//
// Created by llt02 on 11/23/2023.
//

#ifndef AUTEX_OPERATOR_H
#define AUTEX_OPERATOR_H

#include "Grammar.h"

class OperatorGrammar
{
private:
    map<NonTerminal, set<string>> grammarRules;
    map<NonTerminal, set<string>> FirstVT;
    map<NonTerminal, set<string>> LastVT;
    set<string> NonTerminals;
    set<pair<string, string>> aLTb;
    set<pair<string, string>> aEQb;
    set<pair<string, string>> aGTb;

    bool isNonterminal(const string& token);
    bool isOperatorFirstGrammar();

    void calEq();
    map<NonTerminal, vector<string>> calFirstVT();

public:
    explicit OperatorGrammar(Grammar grammar);
};

#endif //AUTEX_OPERATOR_H
