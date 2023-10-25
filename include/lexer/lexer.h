//
// Created by llt02 on 10/25/2023.
//

#ifndef AUTEX_LEXER_H
#define AUTEX_LEXER_H

#include "lexer_utils.h"
#include <string>
#include <vector>
#include <utility>
using namespace std;


class lexer {
private:
    string source_file;
    string target_file;
    string input;
    vector<pair<LX_TYPE, string>> tuples_;

    void analyze();
    void write_tuples();
public:
    lexer(string file, string input);

};


#endif //AUTEX_LEXER_H
