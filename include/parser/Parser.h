//
// Created by llt02 on 11/9/2023.
//

#ifndef AUTEX_PARSER_H
#define AUTEX_PARSER_H

#include "Grammar.h"

#include <utility>
#include <unordered_set>
#include <stack>

using namespace std;


class Token
{
protected:
    string currentInput;
    string token_name;

    void getInput(const string& Input);
public:
    Token(string  token_name) : token_name(std::move(token_name)) {};
    virtual string getName() const = 0;
    virtual void error() = 0;
};

class NonTerminalToken : public Token
{
private:
    vector<string> candidates;
public:
    NonTerminalToken(const string& token_name, const vector<string>& candidates) : Token(token_name), candidates(candidates) {};
    string getName() const override;
    void error() override;
};

class TerminalToken : public Token
{
private:
    bool match(const string& Input);
public:
    TerminalToken(const string& token_name) : Token(token_name) {};
    string getName() const override;
    void error() override;

};

class Parser
{
private:
    stack<string> parserStack;
};




#endif //AUTEX_PARSER_H
