//
// Created by llt02 on 10/23/2023.
//

#include "../include/lexer/lexer_utils.h"

[[maybe_unused]] LX_TYPE lexer_is_letter_(char c)
{
    if(c <= 'z' && c >= 'a') return LX_CHAR_LOWER;
    else if(c <= 'Z' && c >= 'A') return LX_CHAR_UPPER;
    else return LX_CHAR_ERR;
}

