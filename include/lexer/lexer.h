//
// Created by llt02 on 10/25/2023.
//

#ifndef AUTEX_LEXER_H
#define AUTEX_LEXER_H

#include "lexer_utils.h"
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <algorithm>
#include <streambuf>
#include <iostream>
#include <iterator>
using namespace std;


class lexer {
private:
    string source_file;
    const string mid_file = "../test/intermediate/tmp.axm";
    string target_file;
    string input;
    vector<pair<LX_TYPE, string>> tuples_;
    vector<pair<LX_TYPE, string>> cates;

    void analyze();
    void write_tuples();
    void read_file();
    void categorize_();
    void write_();
public:
    lexer(string file, string target);
    void lex(bool verbose);
    void generate();
    vector<pair<LX_TYPE, string>> get_tuples();
    vector<pair<LX_TYPE, string>> get_output();

};


#endif //AUTEX_LEXER_H
