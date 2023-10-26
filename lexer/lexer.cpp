//
// Created by llt02 on 10/25/2023.
//


#include <utility>

#include "../include/lexer/lexer.h"


lexer::lexer(string file, string target) {
    this->source_file = std::move(file);
    this->target_file = std::move(target);
    read_file();
    analyze();
    write_tuples();
    categorize_();
    write_();
}

void lexer::analyze() {
    using NOTE_FLAG = int;
    using LINE_FLAG = int;

    char c = *input.begin();
    NOTE_FLAG noteFlag = 0;
    LINE_FLAG lineFlag = 0;


    for(string::iterator iter = ++input.begin(); iter != input.end(); iter++)
    {
        if(c == '/' and *iter == '*')
        {
            while(c != '*' and *iter != '/')
            {
                iter++;
                c = *iter;
            }
            iter += 2;
            c = *iter;
            continue;
        }

        if(c == '/' and *iter == '/')
        {
            while(c != '\n')
            {
                iter++;
                c = *iter;
            }
            continue;
        }
        if(c == ' ' or c == '\t')
        {
            c = *(iter);
            continue;
        }

        if(c == '\n')
        {
            tuples_.emplace_back(LX_LINE, "\n");
            c = *(iter);
            continue;
        }

        if(lexer_is_letter_(c) == LX_IDF)
        {
            string _tmp;
            _tmp += c;
            while(true)
            {
                c = *iter;
                if(lexer_is_letter_(c) != LX_IDF and lexer_is_digit_(c) != LX_NUM) break;
                iter++;
                _tmp += c;
            }
            cout << _tmp << endl;
            LX_TYPE _type = lexer_is_rsv_tokens_(const_cast<char*>(_tmp.c_str()));
            tuples_.emplace_back(_type, _tmp);
            continue;
        }

        if(lexer_is_digit_(c) == LX_NUM)
        {
            string _tmp;
            _tmp += c;
            while(lexer_is_digit_(c) == LX_NUM)
            {
                c = *iter;
                if(lexer_is_digit_(c) != LX_NUM) break;
                iter++;
                _tmp += c;
            }
            tuples_.emplace_back(LX_NUM, _tmp);
            continue;
        }

        if(lexer_is_symbols_(c) != LX_SYM_ERR)
        {
            string _tmp;
            _tmp += c;
            tuples_.emplace_back(lexer_is_symbols_(c), _tmp);
            c = *iter;
            continue;
        }

        if(lexer_is_single_comparator_(c) != LX_SC_ERR)
        {
            string _tmp;
            _tmp += c;
            c = *(iter++);
            _tmp += c;
            cout << "dc" << _tmp << endl;
            LX_TYPE _type = lexer_is_double_comparator_(lexer_is_single_comparator_(c), c);
            tuples_.emplace_back(_type, _tmp);
            continue;
        }

        if(lexer_is_single_operator_(c) != LX_SO_ERR)
        {
            string _tmp;
            LX_TYPE _type = lexer_is_single_operator_(c);
            _tmp += c;
            iter++;
            c = *iter;
            if(c != '=' and c != '>' and c != '<')
            {
                tuples_.emplace_back(_type, _tmp);
                continue;
            }
            _type = lexer_is_double_operator_(_type, c);
            _tmp += c;
            tuples_.emplace_back(_type, _tmp);
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
    for(auto & iter : tuples_)
    {
        if(iter.first > 100 and iter.first <= 200)
        {
            cates.emplace_back(LX_RESERVED_TOKEN, iter.second);
            continue;
        }

        if(iter.first == LX_USR_IDF)
        {
            cates.emplace_back(LX_USER_TOKEN, iter.second);
            continue;
        }

        if(iter.first > 400 and iter.first < 500 or iter.first > 500 and iter.first < 600)
        {
            cates.emplace_back(LX_MATH_OPR, iter.second);
            continue;
        }

        if(iter.first > 600 and iter.first < 700 or iter.first > 700 and iter.first < 800)
        {
            cates.emplace_back(LX_LOGIC_OPR, iter.second);
            continue;
        }

        if(iter.first > 300 and iter.first <= 400)
        {
            cates.emplace_back(LX_SEPARATOR, iter.second);
            continue;
        }

        if(iter.first == LX_LINE)
        {
            cates.emplace_back(iter);
            continue;
        }

        if(iter.first == LX_NUM)
        {
            cates.emplace_back(LX_UINT, iter.second);
        }
    }
}

vector<pair<LX_TYPE, string>> lexer::get_tuples() {
    return tuples_;
}

vector<pair<LX_TYPE, string>> lexer::get_output() {
    return cates;
}
