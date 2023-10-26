//
// Created by llt02 on 10/25/2023.
//
#include "../include/lexer/lexer.h"


lexer::lexer(string file, string target) {
    this->source_file = std::move(file);
    this->target_file = std::move(target);
    read_file();
}

void lexer::analyze() {
    char c = *input.begin();

    for(string::iterator iter = ++input.begin(); iter != input.end(); c = *iter, iter++)
    {
        if(c == '/' and *iter == '*') {
            iter++;
            while (*iter != '*' and *(iter + 1) != '/') iter++;
            iter += 2;
        }else if(c == '/' and *iter == '/'){
            iter++;
            while(*iter != '\n') iter++;
        }else if(c == ' ' or c == '\t'){
            // do nothing
        }else if(c == '\n'){
            tuples_.emplace_back(LX_LINE, "\n");
        }else if(lexer_is_letter_(c) == LX_IDF)
        {
            string _tmp(1, c);
            while(true)
            {
                c = *iter;
                if(lexer_is_letter_(c) != LX_IDF and lexer_is_digit_(c) != LX_NUM) break;
                iter++;
                _tmp += c;
            }
            LX_TYPE _type = lexer_is_rsv_tokens_(const_cast<char*>(_tmp.c_str()));
            tuples_.emplace_back(_type, _tmp);
        }else if(lexer_is_digit_(c) == LX_NUM){
            string _tmp(1, c);
            while(lexer_is_digit_(c) == LX_NUM)
            {
                c = *(iter++);
                if(lexer_is_digit_(c) != LX_NUM) break;
                _tmp += c;
            }
            tuples_.emplace_back(LX_NUM, _tmp);
        }else if(lexer_is_symbols_(c) != LX_SYM_ERR){
            string _tmp(1, c);
            tuples_.emplace_back(lexer_is_symbols_(c), _tmp);
        }else if(lexer_is_single_comparator_(c) != LX_SC_ERR){
            string _tmp(1, c);
            c = *(iter++);
            _tmp += c;
            LX_TYPE _type = lexer_is_double_comparator_(lexer_is_single_operator_(c), c);
            tuples_.emplace_back(_type, _tmp);
        }else if(lexer_is_single_operator_(c) != LX_SO_ERR){
            string _tmp(1, c);
            LX_TYPE _type = lexer_is_single_operator_(c);
            c = *(iter++);
            if(c != '=' and c != '>' and c != '<')
            {
                tuples_.emplace_back(_type, _tmp);
                continue;
            }
            _type = lexer_is_double_operator_(_type, c);
            _tmp += c;
            tuples_.emplace_back(_type, _tmp);
        }else{
            cerr << "Invalid token." << endl;
        }
    }
}

void lexer::write_tuples() {
    ofstream fw;
    fw.open(mid_file, ios::out);
    if(!fw.is_open()) cerr << "Intermediate file open failed." << endl;
    for(auto & iter : tuples_)
    {
        if(iter.first == LX_LINE)
        {
            fw << endl;
        }
        else
        {
            fw << "(" << iter.first << ", " << iter.second << ") ";
        }
    }
}

void lexer::read_file() {
    ifstream fr;
    fr.open(source_file, ios::in);
    if(!fr.is_open()) cout << "Source file open failed." << endl;
    istreambuf_iterator<char> begin(fr);
    istreambuf_iterator<char> end;
    string _tmp(begin, end);
    input = _tmp;
}

void lexer::write_() {
    ofstream fw;
    fw.open(target_file, ios::out);
    if(!fw.is_open()) cerr << "Target file open failed." << endl;
    for(auto & iter : cates)
    {
        if(iter.first == LX_LINE) fw << endl;
        else fw << "(" << iter.first << ", " << iter.second << ") ";
    }
}

void lexer::categorize_() {
    for(auto & iter : tuples_){
        if(iter.first > 100 and iter.first <= 200){
            cates.emplace_back(LX_RESERVED_TOKEN, iter.second);
        }else if(iter.first == LX_USR_IDF)
        {
            cates.emplace_back(LX_USER_TOKEN, iter.second);
        }else if(iter.first > 400 and iter.first < 500 or iter.first > 500 and iter.first < 600)
        {
            cates.emplace_back(LX_MATH_OPR, iter.second);
        }else if(iter.first > 600 and iter.first < 700 or iter.first > 700 and iter.first < 800)
        {
            cates.emplace_back(LX_LOGIC_OPR, iter.second);
        }else if(iter.first > 300 and iter.first <= 400)
        {
            cates.emplace_back(LX_SEPARATOR, iter.second);
        }else if(iter.first == LX_LINE)
        {
            cates.emplace_back(iter);
        }else if(iter.first == LX_NUM)
        {
            cates.emplace_back(LX_UINT, iter.second);
        }else{
            cerr << "error occurred during categorizing." << endl;
        }
    }
}

vector<pair<LX_TYPE, string>> lexer::get_tuples() {
    return tuples_;
}

vector<pair<LX_TYPE, string>> lexer::get_output() {
    return cates;
}

void lexer::lex(bool verbose) {
    analyze();
    categorize_();
}

void lexer::generate() {
    write_tuples();
    write_();
}

