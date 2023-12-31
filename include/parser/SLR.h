//
// Created by llt02 on 12/4/2023.
//

#ifndef AUTEX_SLR_H
#define AUTEX_SLR_H

#include <utility>
#include <any>

#include "Grammar.h"

struct Rule {
    string head;
    string body;
    Rule(string h, string b) : head(std::move(h)), body(std::move(b)) {}
    bool operator==(const Rule& other) const {
        return head == other.head && body == other.body;
    }
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

struct Transmission {
    Closure source;
    Closure destination;
    string token;

    Transmission(Closure  src, Closure  dest, string  t) : source(std::move(src)), destination(std::move(dest)), token(std::move(t)) {}
    bool operator==(const Transmission& other) const {
        return  source == other.source &&
                destination == other.destination &&
                token == other.token;
    }
};

struct ActionItem {

};

using ActionTable = map<pair<int, string>, string>;
using GotoTable = map<pair<int, string>, int>;

class SimpleLRGrammar
{
private:

    map<NonTerminal, vector<string>> grammarRules;
    vector<Rule> rules;
    ItemSet itemSet;
    set<string> nonTerminalSet;
    set<string> terminalSet;
    string startToken;
    vector<Transmission> transmission;
    map<NonTerminal, FirstSet> firstSets;
    map<NonTerminal, FollowSet> followSets;
    ActionTable actionTable;
    GotoTable gotoTable;

    Closure closure(const vector<LR_Item>& items);
    void getTerminals();
    void fillItemSet();
    void itemSetAdd(const vector<Closure>& cls);
    bool isNonTerminal(const string& token);
    vector<Rule> findRuleOf(const string& head);
    static void closureAdd(const vector<Rule>& forAdds, Closure& c);
    static bool isAdded(const Closure& closure, const LR_Item& item);
    bool isClosureAdded(const Closure& closure);
    static vector<LR_Item> advance(const Closure& closure, const string& token);
    static set<string> findAdvanceTokensIn(const Closure& closure);
    Closure transmit(const Closure& cls, const string& token);
    vector<Closure> emit(const Closure& cls);
    static bool isReduceClosure(const Closure& cls);
    bool isInTransmission(const Transmission& t);
    long long fetchClosureIndex(const Closure& cls);
    static bool hasConflict(const Closure& cls);
    string getActionOf(const string& terminal, const Closure& cls);
    long long getGotoOf(const string& nonTerminal, const Closure& cls);
    long long fetchProductionIndex(const Rule& rule);
    static LR_Item findInClosure(const Closure& cls, const function<bool(const LR_Item&)>& condition);
    void doTable();

    static void printClosure(const Closure& c);
    void printItemSet();
    void printTransmission();
    void printGotoTable();
    void printActionTable();

    //debug
    static void printAdvTokenSet(const set<string>& ATS);
public:
    explicit SimpleLRGrammar(Grammar grammar, int itemSet_alloc_reserve=100);
    void generate();
    void printInfo();
};

#endif //AUTEX_SLR_H
