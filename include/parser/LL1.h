//
// Created by llt02 on 11/8/2023.
//

#ifndef AUTEX_LL1_H
#define AUTEX_LL1_H

#include <iostream>
#include <string>
#include <set>
#include <utility>
#include <vector>
#include <memory>

using namespace std;

typedef struct generative {
    char nt;
    vector<char> candidates;
}GENE;

class Grammar
{
private:
    vector<GENE> grammar;

    void first();
};

class Token
{
private:
    char value;
public:
    Token(char value) : value(value) {}
    char getValue() const {return value;}
    bool operator==(const Token& obj) const;
    bool operator==(const char& obj) const;
    bool isNonTerminal() const;

    Token match(Token expected_token);
    static void error();
};




void S(Token token);

void E(Token token);

void E_prime(Token token);

void T(Token token);

void T_prime(Token token);

void F(Token token);

void A(Token token);

void M(Token token);

void V(Token token);

void match();

void error();

Token getNextToken();



#endif //AUTEX_LL1_H
