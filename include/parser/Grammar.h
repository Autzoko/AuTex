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
public:
    explicit Grammar(const string& grammarFile);
};

#endif //AUTEX_GRAMMAR_H
