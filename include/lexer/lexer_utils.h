//
// Created by llt02 on 10/25/2023.
//

#ifndef AUTEX_LEXER_UTILS_H
#define AUTEX_LEXER_UTILS_H

#include "lexer_defs.h"
#include <cstring>

using LX_TYPE = int;

LX_TYPE lexer_is_letter_(char c);
LX_TYPE lexer_is_digit_(char c);
LX_TYPE lexer_is_rsv_tokens_(char str[]);
LX_TYPE lexer_is_symbols_(char c);
LX_TYPE lexer_is_single_operator_(char c);
LX_TYPE lexer_is_double_operator_(LX_TYPE first_char, char last_char);

#endif //AUTEX_LEXER_UTILS_H
