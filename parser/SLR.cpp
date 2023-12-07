//
// Created by llt02 on 12/4/2023.
//


#include "../include/parser/SLR.h"

SimpleLRGrammar::SimpleLRGrammar(Grammar grammar) {
    grammarRules = grammar.getGrammarRules();
    for(const auto& item : grammarRules) {
        for(const auto& production : item.second) {
            rules.emplace_back(item.first, production);
        }
    }
    nonTerminalSet = grammar.getNonTerminals();
    startToken = grammar.getStartToken();
}

Closure SimpleLRGrammar::closure(const LR_Item &item) {
    Closure result;
    result.push_back(item);
    bool isUpdated = true;
    for(const LR_Item& current : result) {
        string dotTokenOfCurrentItem = string(1, current.rule.body[current.dotPosition]);
        if(isNonTerminal(dotTokenOfCurrentItem)) {
            closureAdd(findRuleOf(dotTokenOfCurrentItem), result);
        }
    }
}

bool SimpleLRGrammar::isNonTerminal(const string &token) {
    if(nonTerminalSet.count(token) != 0) return true;
    else return false;
}

vector<Rule> SimpleLRGrammar::findRuleOf(const string &head) {
    vector<Rule> result;
    for(const auto& item : rules) {
        if(item.head == head) {
            result.push_back(item);
        }
    }
    return result;
}

void SimpleLRGrammar::closureAdd(const vector<Rule> &forAdds, Closure& c) {
    for(const auto& item : forAdds) {
        c.emplace_back(item, 0);
    }
}

void SimpleLRGrammar::emit() {
    LR_Item firstOne = LR_Item(findRuleOf(startToken)[0], 0);
    Closure c = closure(firstOne);
    printClosure(c);
}

void SimpleLRGrammar::printClosure(const Closure &c) {
    for(const auto& item : c) {
        cout << item.rule.head << " -> ";
        for(int i = 0; i < item.rule.body.size(); i++) {
            if(i == item.dotPosition) {
                cout << "•";
            }
            cout << item.rule.body[i];
        }
        cout << endl;
    }
}




