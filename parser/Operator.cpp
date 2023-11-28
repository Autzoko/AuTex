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

void OperatorGrammar::calFirstVT() {
    bool isUpdate = true;
    while(isUpdate) {
        isUpdate = false;
        for(const auto& item : grammarRules) {
            for(const auto& production : item.second) {
                if(!isNonterminal(string(1, production[0]))) {
                    int len = FirstVT[item.first].size();
                    FirstVT[item.first].insert(string(1, production[0]));
                    if(len != FirstVT[item.first].size()) {
                        isUpdate = true;
                    }
                } else {
                    if(production.length() == 1) {
                        string nt = string(1, production[0]);
                        int len = FirstVT[item.first].size();
                        if(!FirstVT[nt].empty()) {
                            set_union(FirstVT[item.first].begin(), FirstVT[item.first].end(), FirstVT[nt].begin(),
                                      FirstVT[nt].end(),
                                      inserter(FirstVT[item.first], FirstVT[item.first].begin()));
                        }
                        if(len != FirstVT[item.first].size()) {
                            isUpdate = true;
                        }
                    } else {
                        string nt = string(1, production[0]);
                        string t = string(1, production[1]);
                        int len = FirstVT[item.first].size();
                        FirstVT[item.first].insert(t);
                        if (!FirstVT[nt].empty()) {
                            set_union(FirstVT[item.first].begin(), FirstVT[item.first].end(), FirstVT[nt].begin(),
                                      FirstVT[nt].end(),
                                      inserter(FirstVT[item.first], FirstVT[item.first].begin()));
                        }
                        if (len != FirstVT[item.first].size()) {
                            isUpdate = true;
                        }
                    }
                }
            }
        }
    }
    for(auto& item : FirstVT) {
        item.second.erase("");
    }
}

void OperatorGrammar::printFirstVT() {
    for(const auto& item : FirstVT) {
        cout << item.first << ": {";
        for(const auto& token : item.second) {
            cout << token << ", ";
        }
        cout << "}" << endl;
    }
    cout << endl;
}

void OperatorGrammar::calLastVT() {
    bool isUpdate = true;
    while(isUpdate) {
        isUpdate = false;
        for(const auto& item : grammarRules) {
            for(const auto& production : item.second) {
                if(!isNonterminal(string(1, production[production.length() - 1]))) {
                    int len = LastVT[item.first].size();
                    string t = string(1, production[production.length() - 1]);
                    LastVT[item.first].insert(t);
                    if(len != LastVT[item.first].size()) {
                        isUpdate = true;
                    }
                } else {
                    if(production.length() == 1) {
                        string nt = string(1, production[production.size() - 1]);
                        int len = LastVT[item.first].size();
                        if(!LastVT[nt].empty()) {
                            set_union(LastVT[item.first].begin(), LastVT[item.first].end(), LastVT[nt].begin(),
                                      LastVT[nt].end(),
                                      inserter(LastVT[item.first], LastVT[item.first].begin()));
                        }
                        if(len != LastVT[item.first].size()) {
                            isUpdate = true;
                        }
                    } else {
                        string nt = string(1, production[production.size() - 1]);
                        string t = string(1, production[production.size() - 2]);
                        int len = LastVT[item.first].size();
                        LastVT[item.first].insert(t);
                        if (!LastVT[nt].empty()) {
                            set_union(LastVT[item.first].begin(), LastVT[item.first].end(), LastVT[nt].begin(),
                                      LastVT[nt].end(),
                                      inserter(LastVT[item.first], LastVT[item.first].begin()));
                        }
                        if (len != LastVT[item.first].size()) {
                            isUpdate = true;
                        }
                    }
                }
            }
        }
    }
    for(auto item : LastVT) {
        item.second.erase("");
    }
}

void OperatorGrammar::printLastVT() {
    for(const auto& item : LastVT) {
        cout << item.first << ": {";
        for(const auto& token : item.second) {
            cout << token << ", ";
        }
        cout << "}" << endl;
    }
    cout << endl;
}

void OperatorGrammar::emit() {
    calFirstVT();
    calLastVT();
}

void OperatorGrammar::printInfo() {
    printFirstVT();
    cout << "---" << endl;
    printLastVT();
}
