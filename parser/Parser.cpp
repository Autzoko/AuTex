//
// Created by llt02 on 11/9/2023.
//


#include "../include/parser/Parser.h"

NonTerminalToken::NonTerminalToken(string token_name, vector<string> candidates) : Token(token_name) {
    this->candidates = std::move(candidates);
}



bool TerminalToken::match(string currentToken) {
    if(currentToken == token_name) return true;
    else return false;
}

void TerminalToken::error() {
    cerr << "Syntax error at token: " << token_name << endl;
    throw std::runtime_error("Invalid token.");
}

void Token::error() {
    cerr << "Syntax error." << endl;
    throw std::runtime_error("Invalid token.");
}
