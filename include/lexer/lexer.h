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
#include <streambuf>
#include <iostream>
#include <iterator>
using namespace std;


class lexer {
private:
    string source_file;
    string target_file;
    string input;
    vector<pair<LX_TYPE, string>> tuples_;

    void analyze();
    void write_tuples();
    void read_file();

    void debug_print_tuples();
    void debug_print_input();
public:
    lexer(string file, string target);

};


#endif //AUTEX_LEXER_H
