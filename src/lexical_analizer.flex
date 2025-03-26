%{
    enum TOKEN : char {
      ID,
      FLOAT_LITERAL,
      INT_LITERAL,
      STRING_LITERAL,
      KW_PROGRAM,
      KW_PROCEDURE,
      KW_BEGIN,
      KW_END,
      KW_IN,
      KW_STRUCT,
      KW_VAR,
      KW_INT,
      KW_FLOAT,
      KW_STRING,
      KW_BOOL,
      KW_REF,
      KW_DEREF,
      KW_RETURN,
      KW_WHILE,
      KW_DO,
      KW_OD,
      KW_IF,
      KW_THEN,
      KW_ELSE,
      KW_FI,
      KW_TRUE,
      KW_FALSE,
      KW_NEW,
      KW_NULL,
      KW_SEMICOLUMN,
      KW_COLUMN,
      KW_COMMA,
      OP_ASSIGN,
      OP_NOT,
      OP_AND,
      OP_OR,
      OP_COMPARE,
      OPEN_PAREN,
      CLOSE_PAREN,
      OPEN_BRACKET,
      CLOSE_BRACKET,
      OPEN_CURLY,
      CLOSE_CURLY
    };
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
    BEGIN(COMMENT);
}
<COMMENT>. {
    // Ignore every character in the comment
}
<COMMENT>"\n" {
    printf("finished comment\n");
    BEGIN(INITIAL);
}
"/*" {
    printf("start multi-line comment\n");
    BEGIN(MULTILINE_COMMENT);
}
<MULTILINE_COMMENT>.|"\n" {
    // Ignore every character
}
<MULTILINE_COMMENT>"*/" {
    printf("finished multi-line comment\n");
    BEGIN(INITIAL);
}

{INT_LITERAL} {
    printf("INT_LITERAL %s\n", yytext);
    return INT_LITERAL;
}
{FLOAT_LITERAL} {
    printf("FLOAT_LITERAL %s\n", yytext);
    return FLOAT_LITERAL;
} 
{STRING_LITERAL} {
    printf("STRING_LITERAL %s\n", yytext);
    return STRING_LITERAL;
}
program {
    printf("KW_PROGRAM \n");
    return KW_PROGRAM;
} 
procedure {
    printf("KW_PROCEDURE \n");
    return KW_PROCEDURE;
} 
begin {
    printf("KW_BEGIN \n");
    return KW_BEGIN;
} 
end {
    printf("KW_END \n");
    return KW_END;
} 
in {
    printf("KW_IN \n");
    return KW_IN;
}
struct {
    printf("KW_STRUCT \n");
    return KW_STRUCT;
} 
var {
    printf("KW_VAR \n");
    return KW_VAR;
} 
int {
    printf("KW_INT \n");
    return KW_INT;
} 
float {
    printf("KW_FLOAT \n");
    return KW_FLOAT;
} 
string {
    printf("KW_STRING \n");
    return KW_STRING;
} 
bool {
    printf("KW_BOOL \n");
    return KW_BOOL;
} 
ref {
    printf("KW_REF \n");
    return KW_REF;
} 
deref {
    printf("KW_DEREF \n");
    return KW_DEREF;
} 
return {
    printf("KW_RETURN \n");
    return KW_RETURN;
} 
while {
    printf("KW_WHILE \n");
    return KW_WHILE;
} 
do {
    printf("KW_DO \n");
    return KW_DO;
} 
od {
    printf("KW_OD \n");
    return KW_OD;
} 
if {
    printf("KW_IF \n");
    return KW_IF;
} 
then {
    printf("KW_THEN \n");
    return KW_THEN;
} 
else {
    printf("KW_ELSE \n");
    return KW_ELSE;
} 
fi {
    printf("KW_FI \n");
    return KW_FI;
} 
true {
    printf("KW_TRUE \n");
    return KW_TRUE;
} 
false {
    printf("KW_FALSE \n");
    return KW_FALSE;
} 
new {
    printf("KW_NEW \n");
    return KW_NEW;
} 
null {
    printf("KW_NULL \n");
    return KW_NULL;
} 
";" {
    printf("KW_SEMICOLUMN\n");
    return KW_SEMICOLUMN;
} 
":" {
    printf("KW_COLUMN\n");
    return KW_COLUMN;
} 
"," {
    printf("KW_COMMA\n");
    return KW_COMMA;
} 
":=" {
    printf("OP_ASSIGN\n");
    return OP_ASSIGN;
} 
not {
    printf("OP_NOT \n");
    return OP_NOT;
} 
"&&" {
    printf("OP_AND \n");
    return OP_AND;
} 
"||" {
    printf("OP_OR \n");
    return OP_OR;
} 
["<"|"<="|">"|">="|"="|"<>"] {
    printf("OP_COMPARE \n");
    return OP_COMPARE;
}
"(" {
    printf("OPEN_PAREN \n");
    return OPEN_PAREN;
} 
")" {
    printf("CLOSE_PAREN \n");
    return CLOSE_PAREN;
} 
"[" {
    printf("OPEN_BRACKET \n");
    return OPEN_BRACKET;
} 
"]" {
    printf("CLOSE_BRACKET \n");
    return CLOSE_BRACKET;
} 
"{" {
    printf("OPEN_CURLY \n");
    return OPEN_CURLY;
} 
"}" {
    printf("CLOSE_CURLY \n");
    return CLOSE_CURLY;
} 
{NAME} {
    printf("ID %s\n", yytext);
    return ID;
} 
" " {
    // Ignore spaces
}
"\n" {
    // Ignore line jumps
}
. {
    printf("INVALID CHAR: %s", yytext);
}

%%
int yywrap() { return 1; }

int main()
{
    enum TOKEN token = yylex();
    while (token) {
        token = yylex();
    }
}
