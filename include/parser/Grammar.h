//
// Created by llt02 on 11/8/2023.
//

#ifndef AUTEX_GRAMMAR_H
#define AUTEX_GRAMMAR_H

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

using FirstSet = set<string>;
using FollowSet = set<string>;
using NonTerminal = string;

class Grammar
{
private:
    map<NonTerminal, vector<string>> grammarRules;
    map<NonTerminal, FirstSet> firstSets;
    map<NonTerminal, FollowSet> followSets;
    set<string> nonTerminalSet;

    bool isNonTerminal(const string& symbol);
public:
    explicit Grammar(const string& grammarFile);
    static vector<string> split(const string& input, char delimiter);
    FirstSet calFirst(const string& symbol);
    map<NonTerminal, FollowSet> calFollow();

    void printGrammar();
    void printFirstSet();
    void printFollowSets();
};

#endif //AUTEX_GRAMMAR_H
