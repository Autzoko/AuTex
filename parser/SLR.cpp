//
// Created by llt02 on 12/4/2023.
//


#include "../include/parser/SLR.h"

SimpleLRGrammar::SimpleLRGrammar(Grammar grammar, int itemSet_alloc_reserve) {
    grammarRules = grammar.getGrammarRules();
    for(const auto& item : grammarRules) {
        for(const auto& production : item.second) {
            rules.emplace_back(item.first, production);
        }
    }
    nonTerminalSet = grammar.getNonTerminals();
    startToken = grammar.getStartToken();
    itemSet.reserve(itemSet_alloc_reserve);
}

Closure SimpleLRGrammar::closure(const LR_Item &item) {
    Closure result;
    result.push_back(item);
    unsigned long long size;
    int current = 0;
    while(true) {
        string dotTokenOfCurrentItem = string(1, result[current].rule.body[result[current].dotPosition]);
        if(isNonTerminal(dotTokenOfCurrentItem)) {
            closureAdd(findRuleOf(dotTokenOfCurrentItem), result);
        }
        size = result.size();
        if(current == size - 1) {
            break;
        }
        current++;
    }
    return result;
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
        LR_Item lrItem = LR_Item(item, 0);
        if(!isAdded(c, lrItem)) {
            c.emplace_back(item, 0);
        }
    }
}

void SimpleLRGrammar::emit() {
    fillItemSet();
    printItemSet();
}

void SimpleLRGrammar::printClosure(const Closure &c) {
    for(const auto& item : c) {
        cout << item.rule.head << " -> ";
        for(int i = 0; i <= item.rule.body.size(); i++) {
            if(i == item.dotPosition) {
                cout << "~";
            }
            cout << item.rule.body[i];
        }
        cout << endl;
    }
}

vector<Closure> SimpleLRGrammar::closuresOf(const Closure &cls) {
    vector<Closure> result;
    for(const auto& item : cls) {
        LR_Item tmp = item;
        if(item.dotPosition < item.rule.body.size()) {
            tmp.dotPosition++;
            result.push_back(closure(tmp));
        }
    }
    return result;
}

void SimpleLRGrammar::printItemSet() {
    for(const auto& item : itemSet) {
        cout << "Closure:" << endl;
        printClosure(item);
        cout << "--------" << endl;
    }
}

void SimpleLRGrammar::fillItemSet() {
    LR_Item firstOne = LR_Item(findRuleOf(startToken)[0], 0);
    itemSet.push_back(closure(firstOne));
    unsigned long long itemSetSize = 0;
    int index = 0;
    while(true) {
        itemSetAdd(closuresOf(itemSet[index]));
        itemSetSize = itemSet.size();
        if(index == itemSetSize) {
            break;
        }
        index++;
    }
}

void SimpleLRGrammar::itemSetAdd(const vector<Closure>& cls) {
    for(const Closure& c : cls) {
        if(!isClosureAdded(c)) {
            itemSet.push_back(c);
        }
    }
}

bool SimpleLRGrammar::isAdded(const Closure &closure, const LR_Item &item) {
    return ranges::any_of(closure.begin(), closure.end(),
                   [item](const LR_Item& lrItem) {
        return lrItem == item;
    });
}

bool SimpleLRGrammar::isClosureAdded(const Closure &closure) {
    return std::ranges::any_of(itemSet.begin(), itemSet.end(),
                               [closure](const Closure& cls) {
        return cls==closure;
    });
}




