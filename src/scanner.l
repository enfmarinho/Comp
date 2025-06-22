%{
#include "parser.tab.hpp"
#include <cstdlib>

    int curr_line = 1, curr_column = 0;

    void update_trivial_info() {
        yylval.general_values.line = curr_line;
        yylval.general_values.column = curr_column;

        curr_column += yyleng;
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
    yylval.int_value.value = std::atoi(yytext);
    yylval.int_value.line = curr_line;
    yylval.int_value.column = curr_column;
    curr_column += yyleng;

    return INT_LITERAL;
}
{FLOAT_LITERAL} {
    yylval.float_value.value = std::atof(yytext);
    yylval.float_value.line = curr_line;
    yylval.float_value.column = curr_column;
    curr_column += yyleng;

    return FLOAT_LITERAL;
} 
{STRING_LITERAL} {
    yylval.string_value.value = new char[yyleng + 1];
    strcpy(yylval.string_value.value, yytext);
    yylval.string_value.line = curr_line;
    yylval.string_value.column = curr_column;
    curr_column += yyleng;

    return STRING_LITERAL;
}
program {
    update_trivial_info();
    return KW_PROGRAM;
} 
procedure {
    update_trivial_info();
    return KW_PROCEDURE;
} 
begin {
    update_trivial_info();
    return KW_BEGIN;
} 
end {
    update_trivial_info();
    return KW_END;
} 
in {
    update_trivial_info();
    return KW_IN;
}
struct {
    update_trivial_info();
    return KW_STRUCT;
} 
var {
    update_trivial_info();
    return KW_VAR;
} 
int {
    update_trivial_info();
    return KW_INT;
} 
float {
    update_trivial_info();
    return KW_FLOAT;
} 
string {
    update_trivial_info();
    return KW_STRING;
} 
bool {
    update_trivial_info();
    return KW_BOOL;
} 
ref {
    update_trivial_info();
    return KW_REF;
} 
deref {
    update_trivial_info();
    return KW_DEREF;
} 
return {
    update_trivial_info();
    return KW_RETURN;
} 
while {
    update_trivial_info();
    return KW_WHILE;
} 
do {
    update_trivial_info();
    return KW_DO;
} 
od {
    update_trivial_info();
    return KW_OD;
} 
if {
    update_trivial_info();
    return KW_IF;
} 
then {
    update_trivial_info();
    return KW_THEN;
} 
else {
    update_trivial_info();
    return KW_ELSE;
} 
fi {
    update_trivial_info();
    return KW_FI;
} 
true {
    update_trivial_info();
    return KW_TRUE;
} 
false {
    update_trivial_info();
    return KW_FALSE;
} 
new {
    update_trivial_info();
    return KW_NEW;
} 
null {
    update_trivial_info();
    return KW_NULL;
} 
";" {
    update_trivial_info();
    return KW_SEMICOLUMN;
} 
":" {
    update_trivial_info();
    return KW_COLUMN;
} 
"," {
    update_trivial_info();
    return KW_COMMA;
} 
"." {
    update_trivial_info();
    return KW_DOT;
} 
exit {
    update_trivial_info();
    return KW_EXIT;
}
when {
    update_trivial_info();
    return KW_WHEN;
}
":=" {
    update_trivial_info();
    return OP_ASSIGN;
} 
not {
    update_trivial_info();
    return OP_NOT;
} 
"+" {
    update_trivial_info();
    return OP_ADD;
} 
"-" {
    update_trivial_info();
    return OP_SUB;
} 
"*" {
    update_trivial_info();
    return OP_MULT;
} 
"/" {
    update_trivial_info();
    return OP_DIV;
} 
"^" {
    update_trivial_info();
    return OP_EXP;
} 
"&&" {
    update_trivial_info();
    return OP_AND;
} 
"||" {
    update_trivial_info();
    return OP_OR;
} 
"<" {
    update_trivial_info();
    return OP_SMALLER;
}
"<=" {
    update_trivial_info();
    return OP_SMALLER_OR_EQ;
}
">" {
    update_trivial_info();
    return OP_GREATER;
}
">=" {
    update_trivial_info();
    return OP_GREATER_OR_EQ;
}
"=" {
    update_trivial_info();
    return OP_EQUAL;
}
"<>" {
    update_trivial_info();
    return OP_NOT_EQUAL;
}
"(" {
    update_trivial_info();
    return OPEN_PAREN;
} 
")" {
    update_trivial_info();
    return CLOSE_PAREN;
} 
"{" {
    update_trivial_info();
    return OPEN_CURLY;
} 
"}" {
    update_trivial_info();
    return CLOSE_CURLY;
} 
{NAME} {
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
