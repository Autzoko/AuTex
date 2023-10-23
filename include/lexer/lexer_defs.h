//
// Created by llt02 on 10/23/2023.
//

#ifndef AUTEX_LEXER_DEFS_H
#define AUTEX_LEXER_DEFS_H

/*Reserved Tokens*/
#define LX_RSV_INT      101
#define LX_RSV_FLOAT    102
#define LX_RSV_DOUBLE   103
#define LX_RSV_CHAR     104
#define LX_RSV_VOID     105
#define LX_RSV_MAIN     106
#define LX_RSV_IF       107
#define LX_RSV_ELIF     108
#define LX_RSV_ELSE     109
#define LX_RSV_WHILE    110
#define LX_RSV_FOR      111
#define LX_RSV_RETURN   112

/*User Identifier*/
#define LX_USR_IDF      201

/*Symbols*/
#define LX_SYM_COMMA    301     // ,
#define LX_SYM_SMCL     302     // ;
#define LX_SYM_DOT      303     // .
#define LX_SYM_LBRC     304     // (
#define LX_SYM_RBRC     305     // )
#define LX_SYM_LBRk     306     // [
#define LX_SYM_RBRK     307     // ]
#define LX_SYM_LCUR     308     // {
#define LX_SYM_RCUR     309     // }
#define LX_SYM_SHARP    310     // #
#define LX_SYM_AT       311     // @
#define LX_SYM_SQM      312     // '
#define LX_SYM_DQm      313     // "

/*Single operator*/
#define LX_SO_ADD       401     // +
#define LX_SO_SUB       402     // -
#define LX_SO_MUL       403     // *
#define LX_SO_DIV       404     // /
#define LX_SO_AND       405     // &
#define LX_SO_OR        406     // |
#define LX_SO_IDIV      407     // %
#define LX_SO_ASSIGN    408     // :


#endif //AUTEX_LEXER_DEFS_H
