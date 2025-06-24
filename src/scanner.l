%{
#include "parser.tab.hpp"
#include <cstdlib>

    int curr_line = 1, curr_column = 0;
    int curr_token_line = 1, curr_token_column = 0;
    int past_token_line = 1, past_token_column = 0;

    void update_trivial_info() {
        yylval.general_values.line = curr_line;
        yylval.general_values.column = curr_column;

        curr_column += yyleng;
    }

    void update_token_pos() {
        past_token_line = curr_token_line;
        past_token_column = curr_token_column;

        curr_token_line = curr_line;
        curr_token_column = curr_column;
    }
%}

%x COMMENT
%x MULTILINE_COMMENT

LETTER [A-Za-z]
NUMBER [0-9]

NAME {LETTER}({LETTER}|{NUMBER}|"_")*({LETTER}|{NUMBER})*

INT_LITERAL {NUMBER}+
FLOAT_LITERAL ({NUMBER}+"."{NUMBER}+)(e["+"|"-"]{NUMBER}{2})?
STRING_LITERAL \".*\"

%%
 // Comment stuff
"//" {
    curr_column += yyleng;
    BEGIN(COMMENT);
}
<COMMENT>. {
    curr_column += yyleng;
    // Ignore every character in the comment
}
<COMMENT>"\n" {
    ++curr_line;
    curr_column = 0;
    BEGIN(INITIAL);
}
"/*" {
    curr_column += yyleng;
    BEGIN(MULTILINE_COMMENT);
}
<MULTILINE_COMMENT>"\n" {
    // Ignore line jumps
    ++curr_line;
    curr_column = 0;
}
<MULTILINE_COMMENT>. {
    // Ignore every character
    curr_column += yyleng;
}
<MULTILINE_COMMENT>"*/" {
    curr_column += yyleng;
    BEGIN(INITIAL);
}

{INT_LITERAL} {
    update_token_pos();

    yylval.int_value.value = std::atoi(yytext);
    yylval.int_value.line = curr_line;
    yylval.int_value.column = curr_column;
    curr_column += yyleng;

    return INT_LITERAL;
}
{FLOAT_LITERAL} {
    update_token_pos();

    yylval.float_value.value = std::atof(yytext);
    yylval.float_value.line = curr_line;
    yylval.float_value.column = curr_column;
    curr_column += yyleng;

    return FLOAT_LITERAL;
} 
{STRING_LITERAL} {
    update_token_pos();

    yylval.string_value.value = new char[yyleng + 1];
    strcpy(yylval.string_value.value, yytext);
    yylval.string_value.line = curr_line;
    yylval.string_value.column = curr_column;
    curr_column += yyleng;

    return STRING_LITERAL;
}
program {
    update_token_pos();
    update_trivial_info();
    return KW_PROGRAM;
} 
procedure {
    update_token_pos();
    update_trivial_info();
    return KW_PROCEDURE;
} 
begin {
    update_token_pos();
    update_trivial_info();
    return KW_BEGIN;
} 
end {
    update_token_pos();
    update_trivial_info();
    return KW_END;
} 
in {
    update_token_pos();
    update_trivial_info();
    return KW_IN;
}
struct {
    update_token_pos();
    update_trivial_info();
    return KW_STRUCT;
} 
var {
    update_token_pos();
    update_trivial_info();
    return KW_VAR;
} 
int {
    update_token_pos();
    update_trivial_info();
    return KW_INT;
} 
float {
    update_token_pos();
    update_trivial_info();
    return KW_FLOAT;
} 
string {
    update_token_pos();
    update_trivial_info();
    return KW_STRING;
} 
bool {
    update_token_pos();
    update_trivial_info();
    return KW_BOOL;
} 
ref {
    update_token_pos();
    update_trivial_info();
    return KW_REF;
} 
deref {
    update_token_pos();
    update_trivial_info();
    return KW_DEREF;
} 
return {
    update_token_pos();
    update_trivial_info();
    return KW_RETURN;
} 
while {
    update_token_pos();
    update_trivial_info();
    return KW_WHILE;
} 
do {
    update_token_pos();
    update_trivial_info();
    return KW_DO;
} 
od {
    update_token_pos();
    update_trivial_info();
    return KW_OD;
} 
if {
    update_token_pos();
    update_trivial_info();
    return KW_IF;
} 
then {
    update_token_pos();
    update_trivial_info();
    return KW_THEN;
} 
else {
    update_token_pos();
    update_trivial_info();
    return KW_ELSE;
} 
fi {
    update_token_pos();
    update_trivial_info();
    return KW_FI;
} 
true {
    update_token_pos();
    update_trivial_info();
    return KW_TRUE;
} 
false {
    update_token_pos();
    update_trivial_info();
    return KW_FALSE;
} 
new {
    update_token_pos();
    update_trivial_info();
    return KW_NEW;
} 
null {
    update_token_pos();
    update_trivial_info();
    return KW_NULL;
} 
";" {
    update_token_pos();
    update_trivial_info();
    return KW_SEMICOLUMN;
} 
":" {
    update_token_pos();
    update_trivial_info();
    return KW_COLUMN;
} 
"," {
    update_token_pos();
    update_trivial_info();
    return KW_COMMA;
} 
"." {
    update_token_pos();
    update_trivial_info();
    return KW_DOT;
} 
exit {
    update_token_pos();
    update_trivial_info();
    return KW_EXIT;
}
when {
    update_token_pos();
    update_trivial_info();
    return KW_WHEN;
}
":=" {
    update_token_pos();
    update_trivial_info();
    return OP_ASSIGN;
} 
not {
    update_token_pos();
    update_trivial_info();
    return OP_NOT;
} 
"+" {
    update_token_pos();
    update_trivial_info();
    return OP_ADD;
} 
"-" {
    update_token_pos();
    update_trivial_info();
    return OP_SUB;
} 
"*" {
    update_token_pos();
    update_trivial_info();
    return OP_MULT;
} 
"/" {
    update_token_pos();
    update_trivial_info();
    return OP_DIV;
} 
"^" {
    update_token_pos();
    update_trivial_info();
    return OP_EXP;
} 
"&&" {
    update_token_pos();
    update_trivial_info();
    return OP_AND;
} 
"||" {
    update_token_pos();
    update_trivial_info();
    return OP_OR;
} 
"<" {
    update_token_pos();
    update_trivial_info();
    return OP_SMALLER;
}
"<=" {
    update_token_pos();
    update_trivial_info();
    return OP_SMALLER_OR_EQ;
}
">" {
    update_token_pos();
    update_trivial_info();
    return OP_GREATER;
}
">=" {
    update_token_pos();
    update_trivial_info();
    return OP_GREATER_OR_EQ;
}
"=" {
    update_token_pos();
    update_trivial_info();
    return OP_EQUAL;
}
"<>" {
    update_token_pos();
    update_trivial_info();
    return OP_NOT_EQUAL;
}
"(" {
    update_token_pos();
    update_trivial_info();
    return OPEN_PAREN;
} 
")" {
    update_token_pos();
    update_trivial_info();
    return CLOSE_PAREN;
} 
"{" {
    update_token_pos();
    update_trivial_info();
    return OPEN_CURLY;
} 
"}" {
    update_token_pos();
    update_trivial_info();
    return CLOSE_CURLY;
} 
{NAME} {
    update_token_pos();

    yylval.id.name = new char[yyleng + 1];
    strcpy(yylval.id.name, yytext);
    yylval.id.line = curr_line;
    yylval.id.column = curr_column;
    curr_column += yyleng;

    return ID;
} 
" " {
    // Ignore spaces
    ++curr_column;
}
"\n" {
    // Ignore line jumps
    ++curr_line;
    curr_column = 0;
}
. {
    printf("INVALID CHAR: %s", yytext);
}

%%

// We can do that, since are only dealing with one file
int yywrap() { return 1; }
