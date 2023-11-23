//
// Created by llt02 on 11/23/2023.
//

#include "../include/parser/Operator.h"

OperatorGrammar::OperatorGrammar(Grammar grammar) {
    grammarRules = grammar.getGrammarRules();
    NonTerminals = grammar.getNonTerminals();
}

bool OperatorGrammar::isNonterminal(const string &token) {
    if(NonTerminals.count(token) == 0) return false;
    else return true;
}

bool OperatorGrammar::isOperatorFirstGrammar() {
    for(auto& item : grammarRules) {
        auto& productions = item.second;
        for(auto& production : productions) {
            size_t len = production.length();
            for(size_t i = 0; i < len - 1; i++) {
                if(isNonterminal(string(1, production[i])) && isNonterminal(string(1, production[i]))) {
                    return false;
                }
            }
        }
    }
    return true;
}

void OperatorGrammar::calEq() {
    for(auto& item : grammarRules) {
        for(auto& production : item.second) {
            size_t len = production.length();
            for(size_t i = 0; i < len - 1; i++) {
                if(!isNonterminal((string(1, production[i])))) {
                    if(!isNonterminal(string(1, production[i + 1]))) {
                        aEQb.insert(make_pair(string(1, production[i]), string(1, production[i + 1])));
                        continue;
                    }
                    if(i < len - 2) {
                        if(isNonterminal(string(1, production[i + 1])) && !isNonterminal(string(1, production[i + 2]))) {
                            aEQb.insert(make_pair(string(1, production[i]), string(1, production[i + 2])));
                            continue;
                        }
                    }
                }
            }
        }
    }
}

map<NonTerminal, vector<string>> OperatorGrammar::calFirstVT() {
    bool isUpdate = true;
    while(isUpdate) {
        for(auto& item : grammarRules) {
            for(auto& production : item.second) {
                if(isNonterminal(string(1, production[0]))) {
                    if(!FirstVT[string(1, production[0])].empty()) {
                        string tmp = string(1, production[0]);

                    }
                } else {
                    FirstVT[item.first].insert(string(1, production[0]));
                    isUpdate = true;
                }
            }
        }
    }
}
