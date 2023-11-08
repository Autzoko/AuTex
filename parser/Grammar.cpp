//
// Created by llt02 on 11/8/2023.
//

#include "../include/parser/Grammar.h"

Grammar::Grammar(const string& grammarFile) {
    ifstream file(grammarFile);
    if(!file.is_open()) {
        cerr << "Failed to open the grammar file." << endl;
        exit(1);
    }
    string line;
    getline(file, line);
    while(getline(file, line)) {
        vector<string> substrs = split(line, ':');
        string nonTerminal = substrs[0];
        nonTerminalSet.insert(nonTerminal);
        vector<string> candidates = split(substrs[1], ',');
        grammarRules.insert(make_pair(nonTerminal, candidates));
    }

    for(auto& item : nonTerminalSet) {
        firstSets.insert(make_pair(item, calFirst(item)));
    }
    for(auto& item : nonTerminalSet) {
        calFollow(item);
    }
}

vector<string> Grammar::split(const string &input, char delimiter) {
    vector<string> substrings;
    size_t start = 0;
    size_t end = input.find(delimiter);

    while(end != string::npos) {
        string token = input.substr(start, end - start);
        substrings.push_back(token);
        start = end + 1;
        end = input.find(delimiter, start);
    }

    string lastToken = input.substr(start);
    substrings.push_back(lastToken);

    return substrings;
}

void Grammar::printGrammar() {
    for(auto & item : grammarRules) {
        cout << item.first << " -> ";
        for(auto & cand : item.second) {
            cout << cand << "|";
        }
        cout << endl;
    }
}

FirstSet Grammar::calFirst(const string &symbol) {
    FirstSet firstSet;
    const auto& rule = grammarRules[symbol];
    for(const string& production : rule) {
        for(char c : production) {
            if(isNonTerminal(string(1, c))) {
                const FirstSet& firstOfNonTerminal = calFirst(string(1, c));
                firstSet.insert(firstOfNonTerminal.begin(), firstOfNonTerminal.end());
                if(firstOfNonTerminal.find("") == firstOfNonTerminal.end()) {
                    break;
                }
            } else if(c != ' ') {
                firstSet.insert(string(1, c));
                break;
            }
        }
    }
    return firstSet;
}

bool Grammar::isNonTerminal(const string &symbol) {
    if(nonTerminalSet.count(symbol) == 0) return false;
    else return true;
}

void Grammar::printFirstSet() {
    for(auto& firstSet : firstSets) {
        cout << firstSet.first << " : ";
        for(auto& item : firstSet.second) {
            cout << item << ", ";
        }
        cout << endl;
    }
}

void Grammar::calFollow(const string &symbol, const string &leftContext) {
    const auto& rule = grammarRules[leftContext];
    for(const string& production : rule) {
        for(size_t i = 0; i < production.length(); ++i) {
            if(production[i] == symbol[0]) {
                if(i + 1 < production.length()) {
                    const FirstSet& firstOfNext = calFirst(string(1, production[i + 1]));
                    followSets[symbol].insert(firstOfNext.begin(), firstOfNext.end());
                    if(firstOfNext.find("") != firstOfNext.end()) {
                        followSets[symbol].erase("");
                        calFollow(symbol, leftContext);
                    }
                } else if(leftContext != "") {
                    calFollow(leftContext);
                    followSets[symbol].insert(followSets[leftContext].begin(), followSets[leftContext].end());
                }
            }
        }
    }
}

void Grammar::printFollowSets() {
    for(auto& followSet : followSets) {
        cout << followSet.first << " : ";
        for(auto& item : followSet.second) {
            cout << item << ", ";
        }
        cout << endl;
    }
}

