//
// Created by llt02 on 11/9/2023.
//

#ifndef AUTEX_PARSER_H
#define AUTEX_PARSER_H

#include <utility>

#include "Grammar.h"

class Token
{
protected:
    string token_name;

    virtual bool match(string currentToken) = 0;
    virtual void error();
public:
    Token(string token_name) : token_name(std::move(token_name)) {};
};

class NonTerminalToken : public Token
{
private:
    vector<string> candidates;
    set<string> firstSet;
    set<string> followSet;

public:
    NonTerminalToken(string token_name, vector<string> candidates);

};

class TerminalToken : public Token
{
protected:
    bool match(string currentToken) override;
    void error() override;
public:
    TerminalToken(string token_name) : Token(std::move(token_name)) {};
};

#endif //AUTEX_PARSER_H
