//
// Created by llt02 on 12/4/2023.
//

#ifndef AUTEX_SLR_H
#define AUTEX_SLR_H

#include "Grammar.h"

typedef struct SLR_closure{
    int closureID;
    vector<map<NonTerminal, string>> item;
    vector<int> pointPOS;
}SLR_CLOSURE;

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
    vector<map<NonTerminal, string>> getMovingInItemsOf(const string& nonTerminal);
public:
    explicit SimpleLRGrammar(Grammar grammar);
};

#endif //AUTEX_SLR_H
