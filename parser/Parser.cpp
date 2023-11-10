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
