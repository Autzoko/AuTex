//
// Created by llt02 on 12/4/2023.
//


#include "../include/parser/SLR.h"

SimpleLRGrammar::SimpleLRGrammar(Grammar grammar) {
    grammarRules = grammar.getGrammarRules();
    startToken = grammar.getStartToken();
    nonTerminals = grammar.getNonTerminals();
    for(const auto& token : nonTerminals) {
        followSets.insert(make_pair(token, grammar.getFollowSetOf(token)));
    }
}

bool SimpleLRGrammar::isNonTerminal(const string &token) {
    if(nonTerminals.count(token) != 0) return true;
    else return false;
}

vector<tuple<NonTerminal, string>> SimpleLRGrammar::getMovingInOf(const string &nonTerminal) {
    vector<string> productions = grammarRules[nonTerminal];
    vector<tuple<NonTerminal, string>> ret;
    ret.reserve(productions.size());
    for(const auto& production : productions) {
        ret.emplace_back(nonTerminal, production);
    }
    return ret;
}

void SimpleLRGrammar::generateClosureSets() {

}

SLR_CLOSURE SimpleLRGrammar::calClosure(const string &nonTerminal, const string &production, const int& pos, const int &id) {
    SLR_CLOSURE ret;
    ret.emplace_back(nonTerminal, production, pos);
    if(isNonTerminal(string(1, production[pos]))) {
        vector<tuple<NonTerminal, string>> tmp = getMovingInOf(string(1, production[pos]));
        for(const auto& item : tmp) {
            ret.emplace_back(std::get<0>(item), std::get<1>(item), 0);
        }
    }
}
