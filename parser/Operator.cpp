//
// Created by llt02 on 11/23/2023.
//

#include "../include/parser/Operator.h"

OperatorGrammar::OperatorGrammar(Grammar grammar) {
    grammarRules = grammar.getGrammarRules();
    NonTerminals = grammar.getNonTerminals();
    Terminals = getTernimals();
    startToken = grammar.getStartToken();
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

void OperatorGrammar::printEq() {
    for(const auto& item : aEQb) {
        cout << item.first << " = " << item.second << endl;
    }
    cout << endl;
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
    calEq();
    calLT();
    calGT();

    setPrecedenceMap();
}

void OperatorGrammar::printInfo() {
    cout << "FirstVT Set:" << endl;
    printFirstVT();
    cout << "LastVT Set:" << endl;
    printLastVT();
    cout << "Equaled Tokens" << endl;
    printEq();
    cout << "LESS THAN Relations:" << endl;
    printLT();
    cout << "GREATER THAN Relations:" << endl;
    printGT();
    cout << "Operator Precedence Table:" << endl;
    printTable();
}

void OperatorGrammar::calLT() {
    for(const auto& item : grammarRules) {
        for(const auto& production : item.second) {
            size_t len = production.length();
            for(size_t i = 0; i < len - 1; i++) {
                string cur = string(1, production[i]);
                string next = string(1, production[i + 1]);
                if(!isNonterminal(cur) && isNonterminal(next)) {
                    set<string> firstVtOfNext = FirstVT[next];
                    for(const auto& token : firstVtOfNext) {
                        aLTb.insert(make_pair(cur, token));
                    }
                }
            }
        }
    }
}

void OperatorGrammar::calGT() {
    for(const auto& item : grammarRules) {
        for(const auto& production : item.second) {
            size_t len = production.length();
            for(size_t i = 0; i < len - 1; i++) {
                string cur = string(1, production[i]);
                string next = string(1, production[i + 1]);
                if(isNonterminal(cur) && !isNonterminal(next)) {
                    set<string> lastVtOfCur = LastVT[cur];
                    for(const auto& token : lastVtOfCur) {
                        aGTb.insert(make_pair(token, next));
                    }
                }
            }
        }
    }
}

void OperatorGrammar::printLT() {
    for(const auto& item : aLTb) {
        cout << item.first << " < " << item.second << endl;
    }
    cout << endl;
}

void OperatorGrammar::printGT() {
    for(const auto& item : aGTb) {
        cout << item.first << " > " << item.second << endl;
    }
    cout << endl;
}

void OperatorGrammar::printTable() {
    for(int i = 0; i < 7 * Terminals.size() - 1; i++) {
        cout << "_";
    }
    cout << endl;
    cout << "|" << setw(5) << std::left << " " << "|";
    for(const auto& col_head : Terminals) {
        cout << setw(5) << std::left << col_head << "|";
    }
    cout << endl;
    for(int i = 0; i < 7 * Terminals.size() - 1; i++) {
        cout << "=";
    }
    cout << endl;
    for(const auto& row : Terminals) {
        cout << "|" << setw(5) << std::left << row << "|";
        for(const auto& col : Terminals) {
            cout << setw(5) << std::left << checkPrecedenceOf(row, col) << "|";
        }
        cout << endl;
        for(int i = 0; i < 7 * Terminals.size() - 1; i++) {
            cout << "-";
        }
        cout << endl;
    }
}

string OperatorGrammar::checkPrecedenceOf(const string &token_a, const string &token_b) {
    if(aLTb.count(make_pair(token_a, token_b)) == 1) {
        return "<";
    } else if(aGTb.count(make_pair(token_a, token_b)) == 1) {
        return ">";
    } else if(aEQb.count(make_pair(token_a, token_b)) == 1) {
        return "=";
    } else {
        return "";
    }
}

set<string> OperatorGrammar::getTernimals() {
    set<string> terminals;
    for(const auto& item : grammarRules) {
        for(const auto& production : item.second) {
            for(const auto& token : production) {
                if(!isNonterminal(string(1, token))) {
                    terminals.insert(string(1, token));
                }
            }
        }
    }
    return terminals;
}

void OperatorGrammar::setPrecedenceMap() {
    for(const auto& a : Terminals) {
        for(const auto& b : Terminals) {
            if(checkPrecedenceOf(a, b) == "<") {
                precedenceMap[make_pair(a, b)] = OPR_LT;
            } else if(checkPrecedenceOf(a, b) == "=") {
                precedenceMap[make_pair(a, b)] = OPR_EQ;
            } else if(checkPrecedenceOf(a, b) == ">") {
                precedenceMap[make_pair(a, b)] = OPR_GT;
            } else {
                continue;
            }
        }
    }
}

map<pair<string, string>, int> OperatorGrammar::getPrecedenceMap() {
    return precedenceMap;
}

set<string> OperatorGrammar::getNonterminals() {
    return NonTerminals;
}

map<NonTerminal, vector<string>> OperatorGrammar::getGrammarRules() {
    return grammarRules;
}

string OperatorGrammar::getStartToken() {
    return startToken;
}

OperatorPrecedentParser::OperatorPrecedentParser(OperatorGrammar operatorGrammar) {
    precedenceMap = operatorGrammar.getPrecedenceMap();
    tokenStack.emplace("#");
    nonTerminal = operatorGrammar.getNonterminals();
    grammarRules = operatorGrammar.getGrammarRules();
    startToken = operatorGrammar.getStartToken();
}

void OperatorPrecedentParser::parse(const string &input) {
    string tmp = input + "#";
    stack<string> inputStack;
    std::reverse(tmp.begin(), tmp.end());
    for(char c : tmp) {
        inputStack.emplace(1, c);
    }
    while(tokenStack.top() != startToken) {
        if(inputStack.empty()) {
            string content = getCurrentStack(tokenStack);
            std::reverse(content.begin(), content.end());
            fetchLog(content, "", "accept");
            reduction();
            continue;
        }
        string firstNT = getFirstNonTerminalInTokenStack();
        if(precedenceMap[make_pair(firstNT, inputStack.top())] == -1) {
            string content = getCurrentStack(tokenStack);
            std::reverse(content.begin(), content.end());
            fetchLog(content, getCurrentStack(inputStack), "move in");
            tokenStack.push(inputStack.top());
            inputStack.pop();
        } else if(precedenceMap[make_pair(firstNT, inputStack.top())] == 0) {
            string content = getCurrentStack(tokenStack);
            std::reverse(content.begin(), content.end());
            fetchLog(content, getCurrentStack(inputStack), "move in");
            tokenStack.push(inputStack.top());
            inputStack.pop();
        } else if(precedenceMap[make_pair(firstNT, inputStack.top())] == 1) {
            while(precedenceMap[make_pair(firstNT, inputStack.top())] == 1) {
                string content = getCurrentStack(tokenStack);
                std::reverse(content.begin(), content.end());
                fetchLog(content, getCurrentStack(inputStack), "reduce");
                reduction();
                firstNT = getFirstNonTerminalInTokenStack();
            }
        } else {
            cerr << "Parser error, token does not follow any precedence relation." << endl;
            exit(3);
        }
    }



}

string OperatorPrecedentParser::getCurrentStack(const stack<string> &s) {
    stack<string> _s = s;
    string ret;
    while(!_s.empty()) {
        ret += _s.top();
        _s.pop();
    }
    return ret;
}

bool OperatorPrecedentParser::isNonterminal(const string &token) {
    if(nonTerminal.count(token) != 0) return true;
    else return false;
}

string OperatorPrecedentParser::getMostLeftDerivation(const string &str) {
    string sentence;
    string result;
    for(int i = 0; i < str.length(); i++) {
        sentence += str[i];
        if(match(sentence)) {
            result = sentence;
        }
    }
    return result;
}

bool OperatorPrecedentParser::match(const string &str) {
    for(const auto& item : grammarRules) {
        for(const auto& production : item.second) {
            if(str == production) {
                return true;
            }
        }
    }
    return false;
}

string OperatorPrecedentParser::getReductionResultOf(const string &production) {
    for(const auto& item : grammarRules) {
        for(const auto& p : item.second) {
            if(p == production) {
                return item.first;
            }
        }
    }
    cerr << "Reduction error: unrecognized production." << endl;
    cerr << "Found error at: " << production << "." << endl;
    exit(3);
}

void OperatorPrecedentParser::reduction() {
    string tokenStackContent = getCurrentStack(tokenStack);
    string mld = getMostLeftDerivation(tokenStackContent);
    size_t lenOfMLD = mld.length();
    string reductionResult = getReductionResultOf(mld);
    while(lenOfMLD--) {
        tokenStack.pop();
    }
    tokenStack.push(reductionResult);
}

string OperatorPrecedentParser::getFirstNonTerminalInTokenStack() {
    string content = getCurrentStack(tokenStack);
    for(char i : content) {
        if(!isNonterminal(string(1, i))) {
            string ret = string(1, i);
            return ret;
        }
    }
    cerr << "Parser error: can not found terminal." << endl;
    exit(3);
}

void OperatorPrecedentParser::emit(const string &input) {
    parse(input);
    cout << "Parse finished." << endl;
}

void OperatorPrecedentParser::printCurrentStack() {
    string content = getCurrentStack(tokenStack);
    std::reverse(content.begin(), content.end());
    cout << content << endl;
}

void OperatorPrecedentParser::fetchLog(const string &stackContent, const string &input, const string &operation) {
    oprLogItem item = oprLogItem(stackContent, input, operation);
    parserLog.push_back(item);
}

void OperatorPrecedentParser::printLog() {
    for(int i = 0; i < 22 * 3 - 2; i++) {
        cout << "_";
    }
    cout << endl;
    cout << "|" << setw(20) << std::left << "Stack" << "|";
    cout << setw(20) << std::left << "Input" << "|";
    cout << setw(20) << std::left << "Operation" << "|" << endl;
    for(int i = 0; i < 22 * 3 - 2; i++) {
        cout << "=";
    }
    cout << endl;
    for(const auto& item : parserLog) {
        cout << "|" << setw(20) << std::left << std::get<0>(item) << "|";
        cout << setw(20) << std::left << std::get<1>(item) << "|";
        cout << setw(20) << std::left << std::get<2>(item) << "|" << endl;
        for(int i = 0; i < 22 * 3 - 2; i++) {
            cout << "-";
        }
        cout << endl;
    }
}
