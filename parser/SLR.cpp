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

void SimpleLRGrammar::generateClosureSets() {

}

bool SimpleLRGrammar::isNonTerminal(const string &token) {
    if(nonTerminals.count(token) != 0) return true;
    else return false;
}

vector<map<NonTerminal, string>> SimpleLRGrammar::getMovingInItemsOf(const string &nonTerminal) {
    return vector<map<NonTerminal, string>>();
}
