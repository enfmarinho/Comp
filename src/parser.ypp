%{
#include <cstdio>
void yyerror(char *s) {
    fprintf(stderr, "line %d: %s", current_line_number, s);
}
%}

%token ID
%token FLOAT_LITERAL
%token INT_LITERAL
%token STRING_LITERAL
%token KW_PROGRAM
%token KW_PROCEDURE
%token KW_BEGIN
%token KW_END
%token KW_IN
%token KW_STRUCT
%token KW_VAR
%token KW_INT
%token KW_FLOAT
%token KW_STRING
%token KW_BOOL
%token KW_REF
%token KW_DEREF
%token KW_RETURN
%token KW_WHILE
%token KW_DO
%token KW_OD
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_FI
%token KW_TRUE
%token KW_FALSE
%token KW_NEW
%token KW_NULL
%token KW_SEMICOLUMN
%token KW_COLUMN
%token KW_COMMA
%token OP_ASSIGN
%token OP_NOT
%token OP_AND
%token OP_OR
%token OP_SMALLER
%token OP_SMALLER_OR_EQ
%token OP_GREATER
%token OP_GREATER_OR_EQ
%token OP_EQUAL
%token OP_NOT_EQUAL
%token OPEN_PAREN
%token CLOSE_PAREN
%token OPEN_BRACKET
%token CLOSE_BRACKET
%token OPEN_CURLY
%token CLOSE_CURLY

%%

type : ID
