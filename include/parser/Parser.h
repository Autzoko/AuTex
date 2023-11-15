//
// Created by llt02 on 11/9/2023.
//

#ifndef AUTEX_PARSER_H
#define AUTEX_PARSER_H

#include "Grammar.h"

#include <utility>
#include <unordered_set>
#include <stack>
#include <iomanip>

using namespace std;

using logItem = tuple<string, string, string, string>;

class Parser
{
private:
    stack<string> tokenStack;
    set<tuple<NonTerminal, string, SelectSet>> selectSets;
    set<string> nonTerminalSet;
    vector<logItem> parserLog;

    void parse(const string& input);
    string getProduction(const string& token, const string& input);
    bool isNonTerminal(const string& token);
    string getCurrentStack() noexcept;
    void fetchLog(const string& stackContent, const string& curInput, const string& seq, const string& select);
public:
    explicit Parser(Grammar grammar);
    void emit(const string& input);
    void printLog() noexcept;
};

class RecursiveDescentParser
{
private:
    int currentIndex;
    vector<string> splitInput;

    void match(const string& expectedToken);
    vector<string> splitBySemicolon(const string& input);
    vector<string> splitBySpace(const string& input);
    vector<string> split(const string& input);
    void parse();

    void S();
    void A_prime();
    void E();
    void L();
    void V();
    void T();
    void E_prime();
    void T_prime();
    void F();
    void M();
    void A();

    void printSplit();

public:
    RecursiveDescentParser();
    void emit(const string& input);
};




#endif //AUTEX_PARSER_H
