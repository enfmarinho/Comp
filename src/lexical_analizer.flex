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

    void insert_simble(char* simble){
        printf("insert simble %s\n", simble);
    }

    void insert_token(enum TOKEN token) {
        printf("insert token ");
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
    insert_token(INT_LITERAL);
    printf("INT_LITERAL %s\n", yytext);
}
{FLOAT_LITERAL} {
    insert_token(FLOAT_LITERAL);
    printf("FLOAT_LITERAL %s\n", yytext);
} 
{STRING_LITERAL} {
    insert_token(STRING_LITERAL);
    printf("STRING_LITERAL %s\n", yytext);
}
program {
    insert_token(KW_PROGRAM);
    printf("KW_PROGRAM \n");
} 
procedure {
    insert_token(KW_PROCEDURE);
    printf("KW_PROCEDURE \n");
} 
begin {
    insert_token(KW_BEGIN);
    printf("KW_BEGIN \n");
} 
end {
    insert_token(KW_END);
    printf("KW_END \n");
} 
in {
    insert_token(KW_IN);
    printf("KW_IN \n");
}
struct {
    insert_token(KW_STRUCT);
    printf("KW_STRUCT \n");
} 
var {
    insert_token(KW_VAR);
    printf("KW_VAR \n");
} 
int {
    insert_token(KW_INT);
    printf("KW_INT \n");
} 
float {
    insert_token(KW_FLOAT);
    printf("KW_FLOAT \n");
} 
string {
    insert_token(KW_STRING);
    printf("KW_STRING \n");
} 
bool {
    insert_token(KW_BOOL);
    printf("KW_BOOL \n");
} 
ref {
    insert_token(KW_REF);
    printf("KW_REF \n");
} 
deref {
    insert_token(KW_DEREF);
    printf("KW_DEREF \n");
} 
return {
    insert_token(KW_RETURN);
    printf("KW_RETURN \n");
} 
while {
    insert_token(KW_WHILE);
    printf("KW_WHILE \n");
} 
do {
    insert_token(KW_DO);
    printf("KW_DO \n");
} 
od {
    insert_token(KW_OD);
    printf("KW_OD \n");
} 
if {
    insert_token(KW_IF);
    printf("KW_IF \n");
} 
then {
    insert_token(KW_THEN);
    printf("KW_THEN \n");
} 
else {
    insert_token(KW_ELSE);
    printf("KW_ELSE \n");
} 
fi {
    insert_token(KW_FI);
    printf("KW_FI \n");
} 
true {
    insert_token(KW_TRUE);
    printf("KW_TRUE \n");
} 
false {
    insert_token(KW_FALSE);
    printf("KW_FALSE \n");
} 
new {
    insert_token(KW_NEW);
    printf("KW_NEW \n");
} 
null {
    insert_token(KW_NULL);
    printf("KW_NULL \n");
} 
";" {
    insert_token(KW_SEMICOLUMN);
    printf("KW_SEMICOLUMN\n");
} 
":" {
    insert_token(KW_COLUMN);
    printf("KW_COLUMN\n");
} 
"," {
    insert_token(KW_COMMA);
    printf("KW_COMMA\n");
} 
":=" {
    insert_token(OP_ASSIGN);
    printf("OP_ASSIGN\n");
} 
not {
    insert_token(OP_NOT);
    printf("OP_NOT \n");
} 
"&&" {
    insert_token(OP_AND);
    printf("OP_AND \n");
} 
"||" {
    insert_token(OP_OR);
    printf("OP_OR \n");
} 
["<"|"<="|">"|">="|"="|"<>"] {
    insert_token(OP_COMPARE);
    printf("OP_COMPARE \n");
}
"(" {
    insert_token(OPEN_PAREN);
    printf("OPEN_PAREN \n");
} 
")" {
    insert_token(CLOSE_PAREN);
    printf("CLOSE_PAREN \n");
} 
"[" {
    insert_token(OPEN_BRACKET);
    printf("OPEN_BRACKET \n");
} 
"]" {
    insert_token(CLOSE_BRACKET);
    printf("CLOSE_BRACKET \n");
} 
"{" {
    insert_token(OPEN_CURLY);
    printf("OPEN_CURLY \n");
} 
"}" {
    insert_token(CLOSE_CURLY);
    printf("CLOSE_CURLY \n");
} 
{NAME} {
    insert_simble(yytext);
    insert_token(ID);
    printf("ID %s\n", yytext);
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
    yylex();
}
