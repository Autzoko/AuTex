//
// Created by llt02 on 10/23/2023.
//

#ifndef AUTEX_LEXER_DEFS_H
#define AUTEX_LEXER_DEFS_H

/*Identifier*/
#define LX_IDF          50
#define LX_NUM          51

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
#define LX_SYM_LBRK     306     // [
#define LX_SYM_RBRK     307     // ]
#define LX_SYM_LCUR     308     // {
#define LX_SYM_RCUR     309     // }
#define LX_SYM_SHARP    310     // #
#define LX_SYM_AT       311     // @
#define LX_SYM_SQM      312     // '
#define LX_SYM_DQM      313     // "

/*Single Operator*/
#define LX_SO_ADD       401     // +
#define LX_SO_SUB       402     // -
#define LX_SO_MUL       403     // *
#define LX_SO_DIV       404     // /
#define LX_SO_AND       405     // &
#define LX_SO_OR        406     // |
#define LX_SO_IDIV      407     // %
#define LX_SO_ASSIGN    408     // =
#define LX_SO_NOT       409     // !
#define LX_SO_XOR       410     // ^

/*Double Operator*/
#define LX_DO_ADDEQU    501     // +=
#define LX_DO_SUBEQU    502     // -=
#define LX_DO_MULEQU    503     // *=
#define LX_DO_DIVEQU    504     // /=
#define LX_DO_ANDEQU    505     // &=
#define LX_DO_OREQU     506     // |=
#define LX_DO_IDIVEQU   507     // %=
#define LX_DO_XOREQU    508     // ^=
#define LX_DO_SHL       509     // <<
#define LX_DO_SHR       510     // >>

/*Single Comparator*/
#define LX_SC_GT        601     // >
#define LX_SC_LT        602     // <

/*Double Comparator*/
#define LX_DC_GE        701     // >=
#define LX_DC_LE        702     // <=
#define LX_DC_EQU       703     // ==
#define LX_DC_NOTEQU    704     // !=

/*Errors*/
#define LX_IDF_ERR          -50
#define LX_NUM_ERR          -51
#define LX_RSV_TOKEN_ERR    -100
#define LX_USR_IDF_ERR      -200
#define LX_SYM_ERR          -300
#define LX_SO_ERR           -400
#define LX_DO_ERR           -500
#define LX_SC_ERR           -600
#define LX_DC_ERR           -700

/*Others*/
#define LX_LINE             801     // \n

/*Category*/
#define LX_RESERVED_TOKEN   1
#define LX_USER_TOKEN       2
#define LX_MATH_OPR         3
#define LX_LOGIC_OPR        4
#define LX_SEPARATOR        5

#endif //AUTEX_LEXER_DEFS_H
