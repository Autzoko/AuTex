//
// Created by llt02 on 11/23/2023.
//

#ifndef AUTEX_OPERATOR_H
#define AUTEX_OPERATOR_H

#include "Grammar.h"
#include "Parser.h"
#include <stack>

#define OPR_LT  -1
#define OPR_GT  1
#define OPR_EQ  0

class OperatorGrammar
{
private:
    map<NonTerminal, vector<string>> grammarRules;
    map<NonTerminal, set<string>> FirstVT;
    map<NonTerminal, set<string>> LastVT;
    set<string> NonTerminals;
    set<string> Terminals;
    set<pair<string, string>> aLTb;
    set<pair<string, string>> aEQb;
    set<pair<string, string>> aGTb;
    map<pair<string, string>, int> precedenceMap;
    string startToken;

    bool isNonterminal(const string& token);
    bool isOperatorFirstGrammar();

    void calFirstVT();
    void printFirstVT();
    void calLastVT();
    void printLastVT();

    void calEq();
    void printEq();
    void calLT();
    void calGT();
    void printLT();
    void printGT();
    void printTable();

    string checkPrecedenceOf(const string& token_a, const string& token_b);
    set<string> getTernimals();
    void setPrecedenceMap();

public:
    explicit OperatorGrammar(Grammar grammar);
    void emit();
    void printInfo();
    map<pair<string, string>, int> getPrecedenceMap();
    set<string> getNonterminals();
    map<NonTerminal, vector<string>> getGrammarRules();
    string getStartToken();
};

using oprLogItem = tuple<string, string, string>;

class OperatorPrecedentParser
{
private:
    map<pair<string, string>, int> precedenceMap;
    stack<string> tokenStack;
    set<NonTerminal> nonTerminal;
    map<NonTerminal, vector<string>> grammarRules;
    string startToken;
    vector<oprLogItem> parserLog;

    void parse(const string& input);
    string getCurrentStack(const stack<string>& s);
    string getMostLeftDerivation(const string& str);
    bool isNonterminal(const string& token);
    bool match(const string& str);
    string getReductionResultOf(const string& production);
    void reduction();
    string getFirstTerminalInTokenStack();
    void fetchLog(const string& stackContent, const string& input, const string& operation);

    //for debug
    void printCurrentStack();
public:
    explicit OperatorPrecedentParser(OperatorGrammar operatorGrammar);
    void emit(const string& input);
    void printLog();
};

#endif //AUTEX_OPERATOR_H
