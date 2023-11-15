//
// Created by llt02 on 11/9/2023.
//


#include "../include/parser/Parser.h"

Parser::Parser(Grammar grammar) {
    selectSets = grammar.getSelectSets();
    tokenStack.emplace("#");
    tokenStack.push(grammar.getStartToken());
    nonTerminalSet = grammar.getNonTerminals();

}

void Parser::parse(const string& input) {
    int stringIndex = 0;
    string inputString = input + "#";
    fetchLog(getCurrentStack(), string(1, inputString[0]), inputString, "");
    while(true) {
        string cur_top = tokenStack.top();
        string useProduction;
        if(cur_top == "#" && tokenStack.size() == 1) {
            cout << "Parsing finished." << endl;
            break;
        }
        char& curChar = inputString[stringIndex];
        if(!isNonTerminal(cur_top)) {
            if(cur_top == string(1, curChar)) {
                stringIndex++;
                tokenStack.pop();
            } else {
                cerr << "Token: " << curChar << " not match." << endl;
                cerr << "Expected: " << cur_top << ", but found: " << curChar << "." << endl;
                throw std::runtime_error("Syntax error");
            }
        } else if(isNonTerminal(cur_top)) {
            string selectProduction = getProduction(cur_top, string(1, curChar));
            if(selectProduction == "e") {
                useProduction = tokenStack.top() + " -> " + selectProduction;
                tokenStack.pop();
            } else {
                useProduction = tokenStack.top() + " -> " + selectProduction;
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
        string sequence = inputString.substr(stringIndex);
        fetchLog(getCurrentStack(), string(1, curChar), sequence, useProduction);
    }
}

string Parser::getProduction(const string& token, const string& input) {
    for(auto& item : selectSets) {
        if(std::get<0>(item) == token && std::get<2>(item).count(input) == 1) {
            return std::get<1>(item);
        }
    }
    cerr << "Can not find SELECT production." << endl;
    cerr << "Error: " << "\"" << input << "\"." << endl;
    throw std::runtime_error("Syntax error");
}

bool Parser::isNonTerminal(const string &token) {
    if(nonTerminalSet.count(token) == 0) return false;
    else return true;
}

void Parser::emit(const string &input) {
    parse(input);
}

string Parser::getCurrentStack() noexcept {
    stack<string> _stack = tokenStack;
    string stackContent;
    while(!_stack.empty()) {
        stackContent += _stack.top();
        _stack.pop();
    }
    std::reverse(stackContent.begin(), stackContent.end());
    return stackContent;
}

void Parser::fetchLog(const string &stackContent, const string &curInput, const string &seq, const string &select) {
    logItem item = logItem(stackContent, curInput, seq, select);
    parserLog.push_back(item);
}

void Parser::printLog() noexcept {
    for(int i = 0; i < 87; i++) {
        cout << "-";
    }
    cout << endl;
    cout << "|";
    cout << setw(20) << std::left << "Token Stack" << "|";
    cout << setw(20) << std::left << "Current Symbol" << "|";
    cout << setw(20) << std::left << "Remain Sequence" << "|";
    cout << setw(22) << std::left << "Selected Production" << "|";
    cout << endl;

    for(int i = 0; i < 87; i++) {
        cout << "=";
    }
    cout << endl;

    for(auto& item : parserLog) {
        cout << "|";
        cout << setw(20) << std::left << std::get<0>(item) << "|";
        cout << setw(20) << std::left << std::get<1>(item) << "|";
        cout << setw(20) << std::left << std::get<2>(item) << "|";
        cout << setw(22) << std::left << std::get<3>(item) << "|";
        cout << endl;
        for(int i = 0; i < 87; i++) {
            cout << "-";
        }
        cout << endl;
    }
}


void RecursiveDescentParser::match(const string &expectedToken) {
    if(currentIndex < splitInput.size() && splitInput[currentIndex] == expectedToken) {
        currentIndex++;
    } else {
        cerr << "Error:" << endl;
        cerr << "Expected: " << expectedToken << ", but found: " << splitInput[currentIndex] << "." << endl;
        exit(3);
    }
}

void RecursiveDescentParser::S() {
    if(splitInput[currentIndex] == "if") {
        match("if");
        E();
        match("then");
        S();
        if(splitInput[currentIndex] == "else") {
            match("else");
            S();
        }
    } else if(splitInput[currentIndex] == "while") {
        match("while");
        E();
        match("do");
        S();
    } else if(splitInput[currentIndex] == "begin") {
        match("begin");
        L();
        match("end");
    } else {
        A();
    }
}


