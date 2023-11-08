//
// Created by llt02 on 11/8/2023.
//

#include "../include/parser/LL1.h"

bool Token::operator==(const Token &obj) const {
    if(this->value == obj.value) return true;
    else return false;
}

bool Token::operator==(const char &obj) const {
    if(this->value == obj) return true;
    else return false;
}

bool Token::isNonTerminal() const {
    if(this->value == 'i') return true;
    else return false;
}

Token Token::match(Token expected_token) {
    if(expected_token == *this) return getNextToken();
    else error();
}

void Token::error() {
    throw std::runtime_error("Syntax error");
}

void S(Token token) {
    if(token.isNonTerminal()) {
        V();
        if(token == '=') {
            token.match('=');
            E();
        } else {
            token.error();
        }
    } else {
        token.error();
    }
}

void E(Token token) {
    T(token);
    E_prime(token);
}

void E_prime(Token token) {
    if(token == '+' || token == '-') {
        A(token);
        T(token);
        E_prime(token);
    }
}

void T(Token token) {
    F(token);
    T_prime(token);
}

void T_prime(Token token) {
    if(token == '*' || token == '/') {
        M(token);
        F(token);
        T_prime(token);
    }
}

void F(Token token) {
    if(token.isNonTerminal()) {
        V(token);
    } else if(token == '(') {
        token.match('(');
        E(token);
        if(token == ')') {
            token.match('(');
        } else {
            token.error();
        }
    } else {
        token.error();
    }
}

void A(Token token) {
    if(token == '+' || token == '-') {
        token.match(token);
    } else {
        token.error();
    }
}

void M(Token token) {
    if(token == '*' || token == '/') {
        token.match(token);
    } else {
        token.error();
    }
}

void V(Token token) {
    if(token == 'i') token.match('i');
    else token.error();
}