//
// Created by llt02 on 10/25/2023.
//

#include "../include/lexer/lexer_utils.h"

LX_TYPE lexer_is_letter_(char c)
{
    if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') return LX_IDF;
    else return LX_IDF_ERR;
}

LX_TYPE lexer_is_digit_(char c)
{
    if(c >= '0' && c <= '9') return LX_NUM;
    else return LX_NUM_ERR;
}

LX_TYPE lexer_is_rsv_tokens_(char str[])
{
    if(strcmp(str, "int") == 0) return LX_RSV_INT;
    else if(strcmp(str, "float") == 0) return LX_RSV_FLOAT;
    else if(strcmp(str, "double") == 0) return LX_RSV_DOUBLE;
    else if(strcmp(str, "char") == 0) return LX_RSV_CHAR;
    else if(strcmp(str, "void") == 0) return LX_RSV_VOID;
    else if(strcmp(str, "main") == 0) return LX_RSV_MAIN;
    else if(strcmp(str, "if") == 0) return LX_RSV_IF;
    else if(strcmp(str, "elif") == 0) return LX_RSV_ELIF;
    else if(strcmp(str, "else") == 0) return LX_RSV_ELSE;
    else if(strcmp(str, "while") == 0) return LX_RSV_WHILE;
    else if(strcmp(str, "for") == 0) return LX_RSV_FOR;
    else if(strcmp(str, "return") == 0) return LX_RSV_RETURN;
    else return LX_USR_IDF;
}

LX_TYPE lexer_is_symbols_(char c)
{
    switch(c)
    {
        case ',': return LX_SYM_COMMA;
        case ';': return LX_SYM_SMCL;
        case '.': return LX_SYM_DOT;
        case '(': return LX_SYM_LBRC;
        case ')': return LX_SYM_RBRC;
        case '[': return LX_SYM_LBRK;
        case ']': return LX_SYM_RBRK;
        case '{': return LX_SYM_LCUR;
        case '}': return LX_SYM_RCUR;
        case '#': return LX_SYM_SHARP;
        case '@': return LX_SYM_AT;
        case '\'': return LX_SYM_SQM;
        case '"': return LX_SYM_DQM;
        default: return LX_SYM_ERR;
    }
}

LX_TYPE lexer_is_single_operator_(char c)
{
    switch(c)
    {
        case '+': return LX_SO_ADD;
        case '-': return LX_SO_SUB;
        case '*': return LX_SO_MUL;
        case '/': return LX_SO_DIV;
        case '&': return LX_SO_AND;
        case '|': return LX_SO_OR;
        case '%': return LX_SO_IDIV;
        case '=': return LX_SO_ASSIGN;
        case '!': return LX_SO_NOT;
        case '^': return LX_SO_XOR;
        default: return LX_SO_ERR;
    }
}

LX_TYPE lexer_is_double_operator_(LX_TYPE first_char, char last_char)
{
    if(last_char == ' ') return first_char;
    else if(last_char == '=')
    {
        switch(first_char)
        {
            case LX_SO_ADD: return LX_DO_ADDEQU;
            case LX_SO_SUB: return LX_DO_SUBEQU;
            case LX_SO_MUL: return LX_DO_MULEQU;
            case LX_SO_DIV: return LX_DO_DIVEQU;
            case LX_SO_AND: return LX_DO_ANDEQU;
            case LX_SO_OR: return LX_DO_OREQU;
            case LX_SO_IDIV: return LX_DO_IDIVEQU;
            case LX_SO_XOR: return LX_DO_XOREQU;
            default: return LX_DO_ERR;
        }
    }
    else if(last_char == '<')
    {
        if(first_char == LX_SC_GT) return LX_DO_SHL;
        else return LX_DO_ERR;
    }
    else if(last_char == '>')
    {
        if(first_char == LX_SC_LT) return LX_DO_SHR;
        else return LX_DO_ERR;
    }
    else
        return LX_DO_ERR;
}