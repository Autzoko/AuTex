//
// Created by llt02 on 12/4/2023.
//

#ifndef AUTEX_SLR_H
#define AUTEX_SLR_H

#include <utility>

#include "Grammar.h"

struct Rule {
    string head;
    string body;
    Rule(string h, string b) : head(std::move(h)), body(std::move(b)) {}
};

struct LR_Item {
    Rule rule;
    int dotPosition;

    LR_Item(Rule r, int dPos) : rule(std::move(r)), dotPosition(dPos) {}
    bool operator==(const LR_Item& other) const {
        return  rule.head == other.rule.head &&
                rule.body == other.rule.body &&
                dotPosition == other.dotPosition;
    }
};

using Closure = vector<LR_Item>;
using ItemSet = vector<Closure>;

using ActionTable = map<pair<int, string>, string>;
using GotoTable = map<pair<int, string>, int>;

class SimpleLRGrammar
{
private:

    map<NonTerminal, vector<string>> grammarRules;
    vector<Rule> rules;
    ItemSet itemSet;
    set<string> nonTerminalSet;
    string startToken;
    map<pair<Closure, string>, Closure> transmission;

    Closure closure(const LR_Item& item);
    vector<Closure> closuresOf(const Closure& cls);
    void fillItemSet();
    void itemSetAdd(const vector<Closure>& cls);
    bool isNonTerminal(const string& token);
    vector<Rule> findRuleOf(const string& head);
    static void closureAdd(const vector<Rule>& forAdds, Closure& c);
    static bool isAdded(const Closure& closure, const LR_Item& item);

    static void printClosure(const Closure& c);
    void printItemSet();
public:
    explicit SimpleLRGrammar(Grammar grammar);
    void emit();
};

#endif //AUTEX_SLR_H
