//
// Created by llt02 on 11/9/2023.
//


#include "../include/parser/Parser.h"

string NonTerminalToken::getName() const {
    return token_name;
}

void NonTerminalToken::error() {
    cerr << "Non-terminal token error: " << token_name << endl;
    throw std::runtime_error("Syntax error.");
}

string TerminalToken::getName() const {
    return token_name;
}

void TerminalToken::error() {
    cerr << "Terminal token error: " << token_name << endl;
    throw std::runtime_error("Syntax error.");
}

bool TerminalToken::match(const string &Input) {
    getInput(Input);
    if(currentInput == token_name) return true;
    else return false;
}

void Token::getInput(const string &Input) {
    currentInput = Input;
}

Parser::Parser(Grammar grammar, const string& input) {
    selectSets = grammar.getSelectSets();
    inputString = input + "#";
    tokenStack.emplace("#");
    tokenStack.push(grammar.getStartToken());
    nonTerminalSet = grammar.getNonTerminals();

    parse();
}

void Parser::parse() {
    int stringIndex = 0;
    while(true) {
        string cur_top = tokenStack.top();
        char& curChar = inputString[stringIndex];
        cout << "top: " << cur_top << endl;
        cout << "char: " << curChar << endl;
        if(!isNonterminal(cur_top)) {
            if(cur_top == string(1, curChar)) {
                stringIndex++;
                tokenStack.pop();
            }
        } else if(isNonterminal(cur_top)) {
            string selectProduction = getProduction(cur_top, string(1, curChar));
            if(selectProduction == "e") {
                tokenStack.pop();
            } else {
                std::reverse(selectProduction.begin(), selectProduction.end());
                tokenStack.pop();
                for(auto& t : selectProduction) {
                    tokenStack.emplace(1, t);
                }
            }
        } else {
            cerr << "stacking parser error." << endl;
            throw std::runtime_error("Parser error");
        }
        if(cur_top == "#" && tokenStack.size() == 1) {
            break;
        }
    }
}

string Parser::getProduction(const string& token, const string& input) {
    for(auto& item : selectSets) {
        if(std::get<0>(item) == token && std::get<2>(item).count(input) == 1) {
            return std::get<1>(item);
        }
    }
    cerr << "Can not find select production." << endl;
    throw std::runtime_error("Parser error");
}

bool Parser::isNonterminal(const string &token) {
    if(nonTerminalSet.count(token) == 0) return false;
    else return true;
}
