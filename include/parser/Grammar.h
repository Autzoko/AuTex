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
#include <tuple>
#include <iomanip>

using namespace std;

using FirstSet = set<string>;
using FollowSet = set<string>;
using SelectSet = set<string>;
using NonTerminal = string;

class Grammar
{
private:
    map<NonTerminal, vector<string>> grammarRules;
    map<NonTerminal, FirstSet> firstSets;
    map<NonTerminal, FollowSet> followSets;
    set<tuple<NonTerminal, string, SelectSet>> selectSets;
    set<string> nonTerminalSet;
    string startToken;

    bool isNonTerminal(const string& symbol);
    static vector<string> split(const string& input, char delimiter);
    FirstSet calFirst(const string& symbol);
    map<NonTerminal, FollowSet> calFollow();
    void calSelect(const NonTerminal& nonTerminal);
    void calAllSelect();
    string setStartToken(const string& firstLine);

    void printGrammar();
    void printFirstSet();
    void printFollowSets();
    void printSelectSets();
public:
    explicit Grammar(const string& grammarFile);
    void emit();

    void printInformation() noexcept;

    map<NonTerminal, vector<string>> getGrammarRules();
    FirstSet getFirstSetOf(const string& token);
    set<tuple<NonTerminal, string, SelectSet>> getSelectSets();
    set<string> getNonTerminals();
    string getStartToken();
};

#endif //AUTEX_GRAMMAR_H
