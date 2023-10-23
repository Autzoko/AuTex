//
// Created by llt02 on 10/23/2023.
//

#ifndef AUTEX_LEXER_DEFS_H
#define AUTEX_LEXER_DEFS_H

/*Reserved Identifiers*/
#define LX_RSV_VOID      0
#define LX_RSV_INT       1
#define LX_RSV_FLOAT     2
#define LX_RSV_DOUBLE    3
#define LX_RSV_IF        4
#define LX_RSV_ELSE      5
#define LX_RSV_FOR       6
#define LX_RSV_DO        7
#define LX_RSV_WHILE     8

/*Identifier*/
#define LX_IDENTIFIER    100

/*Operators*/
#define LX_OPR_ADD       101     // +
#define LX_OPR_SUB       102     // -
#define LX_OPR_MUL       103     // *
#define LX_OPR_DIV       104     // /
#define LX_OPR_SADD      105     // ++
#define LX_OPR_SSUB      106     // --
#define LX_OPR_SHL       107     // <<
#define LX_OPR_SHR       108     // >>
#define LX_OPR_ADDEQ     108     // +=
#define LX_OPR_SUBEQ     109     // -=
#define LX_OPR_MULEQ     110     // *=
#define LX_OPR_DIVEQ     111     // /=
#define LX_OPR_AND       112     // &&
#define LX_OPR_OR        113     // ||
#define LX_OPR_NOT       114     // !



/*Char*/
#define LX_CHAR_UPPER    201
#define LX_CHAR_LOWER    202

/*Exceptions*/
#define LX_GLB_ERR       -1
#define LX_CHAR_ERR      -200



#endif //AUTEX_LEXER_DEFS_H
