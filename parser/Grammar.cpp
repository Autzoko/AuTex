//
// Created by llt02 on 11/8/2023.
//

#include "../include/parser/Grammar.h"

Grammar::Grammar(const string& grammarFile) {
    ifstream file(grammarFile);
    if(!file.is_open()) {
        cerr << "Failed to open the grammar file." << endl;
        exit(1);
    }
    string line;
    while(getline(file, line)) {
        // 把文件内的语法读入到grammarRules里
        // 格式：
        // G[S]    // 规定起始符
        // S:A,T,S
        // A:$e,M
        // T:$+,$- //终结符前必须有$
    }
}
