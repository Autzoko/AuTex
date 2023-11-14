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

    followSets = calFollow();

    calAllSelect();
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

void Grammar::printFollowSets() {
    for(auto& followSet : followSets) {
        cout << followSet.first << " : ";
        for(auto& item : followSet.second) {
            cout << item << ", ";
        }
        cout << endl;
    }
}

map<NonTerminal, FollowSet> Grammar::calFollow() {
    if(firstSets.empty()) {
        cerr << "Invalid FIRST sets, program error." << endl;
        exit(1);
    }
    map<NonTerminal, FollowSet> tmpFollow;
    for(const auto& rule : grammarRules) {
        for(const string& candidate : rule.second) {
            for(int i = 0; i < candidate.length(); i++) {
                char token = candidate[i];
                if(isNonTerminal(string(1, token))) {
                    if(i + 1 == candidate.length()) {
                        tmpFollow[string(1, token)].insert("#");
                        break;
                    }
                    char next = candidate[i + 1];
                    if(!isNonTerminal(string(1, next))) {
                        tmpFollow[string(1, token)].insert(string(1, next));
                    } else {
                        string _next = string(1, next);
                        string _token = string(1, token);
                        set_union(firstSets[_next].begin(), firstSets[_next].end(), tmpFollow[_token].begin(), tmpFollow[_token].end(),
                                  inserter(tmpFollow[_token], tmpFollow[_token].begin()));
                    }
                }
            }
        }
    }
    return tmpFollow;
}

map<NonTerminal, vector<string>> Grammar::getGrammarRules() {
    return grammarRules;
}

FirstSet Grammar::getFirstSetOf(const string& token) {
    return firstSets[token];
}

set<string> Grammar::getNonTerminals() {
    return nonTerminalSet;
}

void Grammar::calSelect(const NonTerminal& nonTerminal) {
    vector<string> rules = grammarRules[nonTerminal];
    using SelectSets = tuple<NonTerminal, string, SelectSet>;
    SelectSets _selectSet;
    for(auto& production : rules) {
        SelectSet _tmp;
        auto& token = production[0];
        if(!isNonTerminal(string(1, token)) && token != 'e') {
            _tmp.insert(string(1, token));
        } else if(!isNonTerminal(string(1, token)) && token == 'e') {
            FollowSet _tmpFollow = followSets[nonTerminal];
            set_union(_tmp.begin(), _tmp.end(), _tmpFollow.begin(), _tmpFollow.end(), inserter(_tmp, _tmp.begin()));
        } else if(isNonTerminal(string(1, token)) && firstSets[string(1, token)].count("e") == 0) {
            FirstSet _tmpSet = firstSets[string(1, token)];
            set_union(_tmp.begin(), _tmp.end(), _tmpSet.begin(), _tmpSet.end(), inserter(_tmp, _tmp.begin()));
        } else if(isNonTerminal(string(1, token)) && firstSets[string(1, token)].count("e") == 1) {
            FollowSet _tmpFollow = followSets[nonTerminal];
            FirstSet _tmpFirst = firstSets[string(1, token)];
            _tmpFirst.erase("e");
            set_union(_tmpFirst.begin(), _tmpFirst.end(), _tmpFollow.begin(), _tmpFollow.end(), inserter(_tmp, _tmp.begin()));
        } else {
            cerr << "Select set error. Mistake found at token \"" << nonTerminal << "\"." << endl;
            throw std::runtime_error("Parser error.");
        }
       selectSets.insert(SelectSets(nonTerminal, production, _tmp));
    }
}

void Grammar::calAllSelect() {
    for(auto& token : nonTerminalSet) {
        calSelect(token);
    }
}

void Grammar::printSelectSets() {
    cout << "-------------------------------------------------------------" << endl;
    cout << "Non-terminal\t|\t" << "Production\t|    " << "Select set     |" << endl;
    cout << "=============================================================" << endl;
    for(auto& item : selectSets) {
        cout << "     " << std::get<0>(item) << "\t\t|\t" << std::get<1>(item) << "\t\t|\t";
        for(auto& token : std::get<2>(item)) {
            cout << token << " ";
        }
        cout << "\t    |" << endl;
        cout << "-------------------------------------------------------------" << endl;
    }
}

