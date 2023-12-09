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

void SimpleLRGrammar::generate() {
    fillItemSet();
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

void SimpleLRGrammar::printItemSet() {
    int index = 0;
    for(const auto& item : itemSet) {
        cout << "Closure " << index++ << ":" << endl;
        printClosure(item);
        cout << "----------------" << endl;
    }
}

void SimpleLRGrammar::fillItemSet() {
    vector<LR_Item> firstOne;
    firstOne.emplace_back(findRuleOf(startToken)[0], 0);
    itemSet.push_back(closure(firstOne));
    unsigned long long itemSetSize = 0;
    int index = 0;
    while(true) {
        itemSetAdd(emit(itemSet[index]));
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

Closure SimpleLRGrammar::closure(const vector<LR_Item> &items) {
    Closure result = items;
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

vector<LR_Item> SimpleLRGrammar::advance(const Closure &closure, const string &token) {
    vector<LR_Item> result;
    for(const LR_Item& item : closure) {
        string advToken = string(1, item.rule.body[item.dotPosition]);
        if(advToken == token && item.dotPosition < item.rule.body.size()) {
            result.emplace_back(item.rule, item.dotPosition + 1);
        }
    }
    return result;
}

set<string> SimpleLRGrammar::findAdvanceTokensIn(const Closure &closure) {
    set<string> result;
    for(const auto& item : closure) {
        string advToken = string(1, item.rule.body[item.dotPosition]);
        if(!result.contains(advToken) && item.dotPosition != item.rule.body.size()) {
            result.insert(advToken);
        }
    }
    return result;
}

Closure SimpleLRGrammar::transmit(const Closure &cls, const string &token) {
    return closure(advance(cls, token));
}

vector<Closure> SimpleLRGrammar::emit(const Closure &cls) {
    set<string> transmit_tokens = findAdvanceTokensIn(cls);
    vector<Closure> result;
    result.reserve(transmit_tokens.size());
    for(const string& token : transmit_tokens) {
        Closure transmit_to = transmit(cls, token);
        result.push_back(transmit_to);
        Transmission tmp = Transmission(cls, transmit_to, token);
        if(!isInTransmission(tmp)) {
            transmission.push_back(tmp);
        }
    }
    return result;
}

void SimpleLRGrammar::printAdvTokenSet(const set<string> &ATS) {
    for(const string& token : ATS) {
        cout << token << endl;
    }
}

bool SimpleLRGrammar::isReduceClosure(const Closure &cls) {
    return ranges::all_of(cls.begin(), cls.end(),
                   [](const LR_Item& item) {
        return item.dotPosition == item.rule.body.size();
    });
}

bool SimpleLRGrammar::isInTransmission(const Transmission &t) {
    return ranges::any_of(transmission.begin(), transmission.end(),
                          [t](const Transmission& trans) {
        return t == trans;
    });
}

void SimpleLRGrammar::printTransmission() {
    cout << "Transmission Table:" << endl;
    for(const auto& t : transmission) {
        cout << "Closure" << fetchClosureIndex(t.source) << ":";
        cout << " --\"" << t.token << "\"--> ";
        cout << "Closure" << fetchClosureIndex(t.destination) << endl;
    }
}

long long SimpleLRGrammar::fetchClosureIndex(const Closure& cls) {
    auto iter = find(itemSet.begin(), itemSet.end(), cls);
    return distance(itemSet.begin(), iter);
}

void SimpleLRGrammar::printInfo() {
    printItemSet();
    printTransmission();
}




