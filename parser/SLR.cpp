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
    SLR_CLOSURE firstClosure = calClosure(startToken, *grammarRules[startToken].begin(), 0);
    closures.push_back(firstClosure);
    for(const auto& closure : closures) {
        auto tmp = calNextClosuresOf(closure);
        for(const auto& item : tmp) {
            closures.push_back(item);
        }
    }
}

SLR_CLOSURE SimpleLRGrammar::calClosure(const string &nonTerminal, const string &production, const int& pos) {
    SLR_CLOSURE ret;
    ret.emplace_back(nonTerminal, production, pos);
    unsigned long long closureLen = 1;
    unsigned long long currentCheckIndex = 0;
    for(;currentCheckIndex < closureLen; currentCheckIndex++) {
        const auto& current = ret[currentCheckIndex];
        if(isNonTerminal(string(1, std::get<1>(current)[std::get<2>(current)]))) {
            auto tmp = getMovingInOf(string(1, std::get<1>(current)[std::get<2>(current)]));
            for(const auto& item : tmp) {
                ret.emplace_back(std::get<0>(item), std::get<1>(item), 0);
            }
            closureLen += tmp.size();
        }
    }
    return ret;
}

vector<SLR_CLOSURE> SimpleLRGrammar::calNextClosuresOf(SLR_CLOSURE c) {
    vector<SLR_CLOSURE> ret;
    for(const auto& item : c) {
        NonTerminal nt = std::get<0>(item);
        string pd = std::get<1>(item);
        int pos = std::get<2>(item);
        SLR_CLOSURE tmp = calClosure(nt, pd, pos + 1);
        ret.push_back(tmp);
    }
    return ret;
}
