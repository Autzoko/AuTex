//
// Created by llt02 on 11/23/2023.
//

#ifndef AUTEX_OPERATOR_H
#define AUTEX_OPERATOR_H

#include "Grammar.h"

class OperatorGrammar
{
private:
    map<NonTerminal, vector<string>> grammarRules;
    map<NonTerminal, set<string>> FirstVT;
    map<NonTerminal, set<string>> LastVT;
    set<string> NonTerminals;
    set<pair<string, string>> aLTb;
    set<pair<string, string>> aEQb;
    set<pair<string, string>> aGTb;

    bool isNonterminal(const string& token);
    bool isOperatorFirstGrammar();

    void calEq();
    void calFirstVT();
    void printFirstVT();
    void calLastVT();
    void printLastVT();


public:
    explicit OperatorGrammar(Grammar grammar);
    void emit();
    void printInfo();
};

#endif //AUTEX_OPERATOR_H
