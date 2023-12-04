//
// Created by llt02 on 12/4/2023.
//

#ifndef AUTEX_SLR_H
#define AUTEX_SLR_H

#include "Grammar.h"

using SLR_CLOSURE = vector<tuple<NonTerminal, string, int>>;

class SimpleLRGrammar
{
private:
    map<NonTerminal, vector<string>> grammarRules;
    string startToken;
    set<string> nonTerminals;
    map<NonTerminal, FollowSet> followSets;
    vector<SLR_CLOSURE> closures;

    void generateClosureSets();
    bool isNonTerminal(const string& token);
    vector<tuple<NonTerminal, string>> getMovingInOf(const string& nonTerminal);
    SLR_CLOSURE calClosure(const string& nonTerminal, const string& production, const int& pos, const int& id);
public:
    explicit SimpleLRGrammar(Grammar grammar);
};

#endif //AUTEX_SLR_H
