//
// Created by llt02 on 10/25/2023.
//


#include "../include/lexer/lexer.h"


lexer::lexer(string file, string target) {
    this->target_file = std::move(file);
    this->target_file = std::move(target);
    cout << "read file" << endl;
    read_file();
    cout << "analyze" << endl;
    debug_print_input();
    analyze();
    cout << "write tuples" << endl;
    write_tuples();
}

void lexer::analyze() {
    using NOTE_FLAG = int;
    using LINE_FLAG = int;

    char c = *input.begin();
    NOTE_FLAG noteFlag = 0;
    LINE_FLAG lineFlag = 0;

    for(auto & iter : input)
    {
        if(iter == ' ' or iter == '\t')
        {
            c = ++iter;
            continue;
        }

        if(c == '\n')
        {
            tuples_.emplace_back(LX_LINE, "\n");
            c = ++iter;
            continue;
        }

        if(lexer_is_letter_(c) == LX_IDF)
        {
            string _tmp;
            _tmp += c;
            while(lexer_is_letter_(c) == LX_IDF or lexer_is_digit_(c) == LX_NUM)
            {
                c = ++iter;
                _tmp += c;
            }
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
                c = ++iter;
                _tmp += c;
            }
            tuples_.emplace_back(LX_NUM, _tmp);
            continue;
        }

        if(lexer_is_symbols_(c) != LX_SYM_ERR)
        {
            tuples_.emplace_back(lexer_is_symbols_(c), string(reinterpret_cast<const char *>(c)));
            continue;
        }
        else
        {
            tuples_.emplace_back(LX_SYM_ERR, string(reinterpret_cast<const char *>(c)));
            continue;
        }

        if(lexer_is_single_comparator_(c) != LX_SC_ERR)
        {
            string _tmp;
            _tmp += c;
            c = ++iter;
            _tmp += c;
            LX_TYPE _type = lexer_is_double_comparator_(lexer_is_single_comparator_(c), c);
            tuples_.emplace_back(_type, _tmp);
            continue;
        }

        if(lexer_is_single_operator_(c) != LX_SO_ERR)
        {
            string _tmp;
            _tmp += c;
            c = ++iter;
            _tmp += c;
            LX_TYPE _type = lexer_is_double_operator_(lexer_is_single_operator_(c), c);
            tuples_.emplace_back(_type, _tmp);
            continue;
        }
    }
}

void lexer::write_tuples() {
    ofstream fw;
    fw.open(target_file, ios::out);
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
    ifstream fr(source_file);
    string _tmp((istreambuf_iterator<char>(fr)), istreambuf_iterator<char>());
    input = _tmp;
}

void lexer::debug_print_tuples() {
    for(auto & iter : tuples_)
    {
        cout << "(" << iter.first << ", " << iter.second << ")" << endl;
    }
}

void lexer::debug_print_input() {
    cout << input << endl;
}
