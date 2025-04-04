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

INT_LITERAL "-"?{NUMBER}+
FLOAT_LITERAL "-"?({NUMBER}+"."{NUMBER}+)(e["+"|"-"]{NUMBER}{2})?
STRING_LITERAL \".*\"

%%
 // TODO remove these print statements

 // Comment stuff
"//" {
    printf("start comment\n");
    curr_column += yyleng;
    BEGIN(COMMENT);
}
<COMMENT>. {
    curr_column += yyleng;
    // Ignore every character in the comment
}
<COMMENT>"\n" {
    printf("finished comment\n");
    ++curr_line;
    curr_column = 0;
    BEGIN(INITIAL);
}
"/*" {
    printf("start multi-line comment\n");
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
    printf("finished multi-line comment\n");
    curr_column += yyleng;
    BEGIN(INITIAL);
}

{INT_LITERAL} {
    yylval.int_value.value = std::atoi(yytext);
    yylval.int_value.line = curr_line;
    yylval.int_value.column = curr_column;
    curr_column += yyleng;

    printf("INT_LITERAL %s\n", yytext);
    return INT_LITERAL;
}
{FLOAT_LITERAL} {
    yylval.float_value.value = std::atof(yytext);
    yylval.float_value.line = curr_line;
    yylval.float_value.column = curr_column;
    curr_column += yyleng;

    printf("FLOAT_LITERAL %s\n", yytext);
    return FLOAT_LITERAL;
} 
{STRING_LITERAL} {
    yylval.string_value.value = new char[yyleng + 1];
    strcpy(yylval.string_value.value, yytext);
    yylval.string_value.line = curr_line;
    yylval.string_value.column = curr_column;
    curr_column += yyleng;

    printf("STRING_LITERAL %s\n", yytext);
    return STRING_LITERAL;
}
program {
    update_trivial_info();
    printf("KW_PROGRAM \n");
    return KW_PROGRAM;
} 
procedure {
    update_trivial_info();
    printf("KW_PROCEDURE \n");
    return KW_PROCEDURE;
} 
begin {
    update_trivial_info();
    printf("KW_BEGIN \n");
    return KW_BEGIN;
} 
end {
    update_trivial_info();
    printf("KW_END \n");
    return KW_END;
} 
in {
    update_trivial_info();
    printf("KW_IN \n");
    return KW_IN;
}
struct {
    update_trivial_info();
    printf("KW_STRUCT \n");
    return KW_STRUCT;
} 
var {
    update_trivial_info();
    printf("KW_VAR \n");
    return KW_VAR;
} 
int {
    update_trivial_info();
    printf("KW_INT \n");
    return KW_INT;
} 
float {
    update_trivial_info();
    printf("KW_FLOAT \n");
    return KW_FLOAT;
} 
string {
    update_trivial_info();
    printf("KW_STRING \n");
    return KW_STRING;
} 
bool {
    update_trivial_info();
    printf("KW_BOOL \n");
    return KW_BOOL;
} 
ref {
    update_trivial_info();
    printf("KW_REF \n");
    return KW_REF;
} 
deref {
    update_trivial_info();
    printf("KW_DEREF \n");
    return KW_DEREF;
} 
return {
    update_trivial_info();
    printf("KW_RETURN \n");
    return KW_RETURN;
} 
while {
    update_trivial_info();
    printf("KW_WHILE \n");
    return KW_WHILE;
} 
do {
    update_trivial_info();
    printf("KW_DO \n");
    return KW_DO;
} 
od {
    update_trivial_info();
    printf("KW_OD \n");
    return KW_OD;
} 
if {
    update_trivial_info();
    printf("KW_IF \n");
    return KW_IF;
} 
then {
    update_trivial_info();
    printf("KW_THEN \n");
    return KW_THEN;
} 
else {
    update_trivial_info();
    printf("KW_ELSE \n");
    return KW_ELSE;
} 
fi {
    update_trivial_info();
    printf("KW_FI \n");
    return KW_FI;
} 
true {
    update_trivial_info();
    printf("KW_TRUE \n");
    return KW_TRUE;
} 
false {
    update_trivial_info();
    printf("KW_FALSE \n");
    return KW_FALSE;
} 
new {
    update_trivial_info();
    printf("KW_NEW \n");
    return KW_NEW;
} 
null {
    update_trivial_info();
    printf("KW_NULL \n");
    return KW_NULL;
} 
";" {
    update_trivial_info();
    printf("KW_SEMICOLUMN\n");
    return KW_SEMICOLUMN;
} 
":" {
    update_trivial_info();
    printf("KW_COLUMN\n");
    return KW_COLUMN;
} 
"," {
    update_trivial_info();
    printf("KW_COMMA\n");
    return KW_COMMA;
} 
"." {
    update_trivial_info();
    printf("KW_DOT\n");
    return KW_DOT;
} 
":=" {
    update_trivial_info();
    printf("OP_ASSIGN\n");
    return OP_ASSIGN;
} 
not {
    update_trivial_info();
    printf("OP_NOT \n");
    return OP_NOT;
} 
"+" {
    update_trivial_info();
    printf("OP_ADD \n");
    return OP_ADD;
} 
"-" {
    update_trivial_info();
    printf("OP_SUB \n");
    return OP_SUB;
} 
"*" {
    update_trivial_info();
    printf("OP_MULT \n");
    return OP_MULT;
} 
"/" {
    update_trivial_info();
    printf("OP_DIV \n");
    return OP_DIV;
} 
"^" {
    update_trivial_info();
    printf("OP_EXP \n");
    return OP_EXP;
} 
"&&" {
    update_trivial_info();
    printf("OP_AND \n");
    return OP_AND;
} 
"||" {
    update_trivial_info();
    printf("OP_OR \n");
    return OP_OR;
} 
"<" {
    update_trivial_info();
    printf("OP_SMALLER \n");
    return OP_SMALLER;
}
"<=" {
    update_trivial_info();
    printf("OP_SMALLER_OR_EQ \n");
    return OP_SMALLER_OR_EQ;
}
">" {
    update_trivial_info();
    printf("OP_GREATER \n");
    return OP_GREATER;
}
">=" {
    update_trivial_info();
    printf("OP_GREATER_OR_EQ \n");
    return OP_GREATER_OR_EQ;
}
"=" {
    update_trivial_info();
    printf("OP_EQUAL \n");
    return OP_EQUAL;
}
"<>" {
    update_trivial_info();
    printf("OP_NOT_EQUAL \n");
    return OP_NOT_EQUAL;
}
"(" {
    update_trivial_info();
    printf("OPEN_PAREN \n");
    return OPEN_PAREN;
} 
")" {
    update_trivial_info();
    printf("CLOSE_PAREN \n");
    return CLOSE_PAREN;
} 
"{" {
    update_trivial_info();
    printf("OPEN_CURLY \n");
    return OPEN_CURLY;
} 
"}" {
    update_trivial_info();
    printf("CLOSE_CURLY \n");
    return CLOSE_CURLY;
} 
{NAME} {
    yylval.id.simble = new char[yyleng + 1];
    strcpy(yylval.id.simble, yytext);
    yylval.id.line = curr_line;
    yylval.id.column = curr_column;
    curr_column += yyleng;

    printf("ID %s\n", yytext);
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
