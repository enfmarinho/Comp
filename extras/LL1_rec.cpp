#include "../build/lex.yy.cc"
#include "../build/parser.tab.hpp"
#include <cstdlib>
#include <iostream>
#define SymbolType int
SymbolType token = yylex();
YYSTYPE yylval;
void error() {
  int line, column;
  if (token == INT_LITERAL) {
    line = yylval.int_value.line;
    column = yylval.int_value.column;
  } else if (token == FLOAT_LITERAL) {
    line = yylval.float_value.line;
    column = yylval.float_value.column;
  } else if (token == STRING_LITERAL) {
    line = yylval.string_value.line;
    column = yylval.string_value.column;
  } else if (token == ID) {
    line = yylval.id.line;
    column = yylval.id.column;
  } else {
    line = yylval.general_values.line;
    column = yylval.general_values.column;
  }
  std::cout << "Error at line " << line << " and at column " << column;
  exit(1);
}
void process_input(SymbolType expected_token) {
  if (token != expected_token)
    error();
  else
    token = yylex();
}
void f_DO_STMT_LIST();
void f_DO_STMT();
void f_U_CALL_STMT();
void f_L2_EXP();
void f_LU2_EXP();
void f_R_EXP();
void f_RETURN_STMT();
void f_OPT_EXP();
void f_PARAMFIELD_DECL();
void f_NAME_VAR();
void f_EXP();
void f_VAR();
void f_Z_PROC_DECL();
void f_STMT_LIST();
void f_LU_EXP();
void f_S();
void f_U_PROGRAM();
void f_PROC_DECL();
void f_PROGRAM();
void f_Y_PROC_DECL();
void f_U_VAR_DECL();
void f_ASSIGN_STMT();
void f_POW_EXP();
void f_T_PROGRAM();
void f_T_REC_DECL();
void f_V_PROC_DECL();
void f_REC_DECL();
void f_POW_EXP2();
void f_NAME_CALL_STMT();
void f_X_PROC_DECL();
void f_VAR_DECL();
void f_L_EXP();
void f_STMT();
void f_T_VAR_DECL();
void f_U_REC_DECL();
void f_T_PROC_DECL();
void f_AU_EXP();
void f_A_EXP();
void f_WHILE_STMT();
void f_A2_EXP();
void f_AU2_EXP();
void f_FIM_EXP();
void f_NAME_STMT();
void f_REF_VAR();
void f_NO_PAREN_VAR();
void f_DEREF_VAR();
void f_T_STMT_LIST();
void f_NAME_ASSIGN_STMT();
void f_REC_VAR();
void f_NAMELESS_DEREF_VAR_VAR();
void f_TYPE();
void f_T_CALL_STMT();
void f_NAMELESS_VAR();
void f_LITERAL();
void f_DECL();
void f_T_IF_STMT();
void f_R2_EXP();
void f_BOOL_LITERAL();
void f_OPT_DOT_NAME_ASSIGN_EXP();
void f_OPT_DOT_NAME();
void f_NAMELESS_ASSIGN_STMT();
void f_U_PROC_DECL();
void f_IF_STMT();
void f_CALL_STMT();
int main() {
  f_S();
  std::cout << "Input belongs to grammar!" << std::endl;
}
void f_DO_STMT_LIST() {
  switch (token) {
  case KW_RETURN:
    f_RETURN_STMT();
    break;
  case KW_OD:
    break;
  case KW_EXIT:
    process_input(KW_EXIT);
    process_input(KW_WHEN);
    f_EXP();
    break;
  case KW_DO:
    f_DO_STMT();
    break;
  case KW_IF:
    f_IF_STMT();
    break;
  case KW_DEREF:
    f_NAMELESS_ASSIGN_STMT();
    break;
  case ID:
    process_input(ID);
    f_NAME_STMT();
    break;
  default:
    error();
  }
}
void f_DO_STMT() {
  switch (token) {
  case KW_DO:
    process_input(KW_DO);
    f_DO_STMT_LIST();
    process_input(KW_OD);
    break;
  default:
    error();
  }
}
void f_U_CALL_STMT() {
  switch (token) {
  case KW_COMMA:
    process_input(KW_COMMA);
    f_EXP();
    f_U_CALL_STMT();
    break;
  case CLOSE_PAREN:
    break;
  default:
    error();
  }
}
void f_L2_EXP() {
  switch (token) {
  case KW_DO:
    break;
  case KW_ELSE:
    break;
  case KW_TRUE:
    break;
  case KW_FI:
    break;
  case KW_FALSE:
    break;
  case KW_NULL:
    break;
  case INT_LITERAL:
    break;
  case ID:
    break;
  case KW_DEREF:
    break;
  case KW_SEMICOLUMN:
    break;
  case OPEN_PAREN:
    break;
  case KW_END:
    break;
  case CLOSE_PAREN:
    break;
  case KW_THEN:
    break;
  case KW_REF:
    break;
  case KW_COMMA:
    break;
  case OP_OR:
    process_input(OP_OR);
    f_LU_EXP();
    f_L2_EXP();
    break;
  case KW_IN:
    break;
  case KW_OD:
    break;
  case OP_NOT:
    break;
  case STRING_LITERAL:
    break;
  case KW_NEW:
    break;
  case FLOAT_LITERAL:
    break;
  default:
    error();
  }
}
void f_LU2_EXP() {
  switch (token) {
  case KW_DO:
    break;
  case KW_TRUE:
    break;
  case KW_FI:
    break;
  case KW_FALSE:
    break;
  case KW_NULL:
    break;
  case INT_LITERAL:
    break;
  case FLOAT_LITERAL:
    break;
  case ID:
    break;
  case KW_DEREF:
    break;
  case KW_SEMICOLUMN:
    break;
  case OPEN_PAREN:
    break;
  case KW_ELSE:
    break;
  case OP_AND:
    process_input(OP_AND);
    f_R_EXP();
    f_LU2_EXP();
    break;
  case KW_END:
    break;
  case CLOSE_PAREN:
    break;
  case KW_THEN:
    break;
  case KW_REF:
    break;
  case KW_COMMA:
    break;
  case OP_OR:
    break;
  case KW_IN:
    break;
  case KW_OD:
    break;
  case OP_NOT:
    break;
  case STRING_LITERAL:
    break;
  case KW_NEW:
    break;
  default:
    error();
  }
}
void f_R_EXP() {
  switch (token) {
  case KW_TRUE:
    f_A_EXP();
    f_R2_EXP();
    break;
  case KW_FALSE:
    f_A_EXP();
    f_R2_EXP();
    break;
  case KW_NULL:
    f_A_EXP();
    f_R2_EXP();
    break;
  case STRING_LITERAL:
    f_A_EXP();
    f_R2_EXP();
    break;
  case INT_LITERAL:
    f_A_EXP();
    f_R2_EXP();
    break;
  case FLOAT_LITERAL:
    f_A_EXP();
    f_R2_EXP();
    break;
  case OP_NOT:
    f_A_EXP();
    f_R2_EXP();
    break;
  case OPEN_PAREN:
    f_A_EXP();
    f_R2_EXP();
    break;
  case KW_DEREF:
    f_A_EXP();
    f_R2_EXP();
    break;
  case ID:
    f_A_EXP();
    f_R2_EXP();
    break;
  default:
    error();
  }
}
void f_RETURN_STMT() {
  switch (token) {
  case KW_RETURN:
    process_input(KW_RETURN);
    f_EXP();
    break;
  default:
    error();
  }
}
void f_OPT_EXP() {
  switch (token) {
  case KW_DO:
    break;
  case KW_ELSE:
    break;
  case KW_TRUE:
    f_EXP();
    break;
  case KW_FI:
    break;
  case KW_FALSE:
    f_EXP();
    break;
  case KW_NULL:
    f_EXP();
    break;
  case ID:
    f_EXP();
    break;
  case KW_DEREF:
    f_EXP();
    break;
  case KW_SEMICOLUMN:
    break;
  case OPEN_PAREN:
    f_EXP();
    break;
  case KW_END:
    break;
  case CLOSE_PAREN:
    break;
  case KW_THEN:
    break;
  case KW_REF:
    f_EXP();
    break;
  case KW_COMMA:
    break;
  case KW_IN:
    break;
  case KW_OD:
    break;
  case OP_NOT:
    f_EXP();
    break;
  case STRING_LITERAL:
    f_EXP();
    break;
  case KW_NEW:
    f_EXP();
    break;
  case FLOAT_LITERAL:
    f_EXP();
    break;
  case INT_LITERAL:
    f_EXP();
    break;
  default:
    error();
  }
}
void f_PARAMFIELD_DECL() {
  switch (token) {
  case ID:
    process_input(ID);
    process_input(KW_COLUMN);
    f_TYPE();
    break;
  default:
    error();
  }
}
void f_NAME_VAR() {
  switch (token) {
  case CLOSE_PAREN:
    break;
  case OPEN_PAREN:
    f_NAME_CALL_STMT();
    process_input(KW_DOT);
    process_input(ID);
    break;
  case OP_ASSIGN:
    break;
  default:
    error();
  }
}
void f_EXP() {
  switch (token) {
  case KW_TRUE:
    f_L_EXP();
    f_OPT_EXP();
    break;
  case INT_LITERAL:
    f_L_EXP();
    f_OPT_EXP();
    break;
  case FLOAT_LITERAL:
    f_L_EXP();
    f_OPT_EXP();
    break;
  case KW_NULL:
    f_L_EXP();
    f_OPT_EXP();
    break;
  case STRING_LITERAL:
    f_L_EXP();
    f_OPT_EXP();
    break;
  case KW_REF:
    f_REF_VAR();
    break;
  case OP_NOT:
    f_L_EXP();
    f_OPT_EXP();
    break;
  case KW_FALSE:
    f_L_EXP();
    f_OPT_EXP();
    break;
  case KW_NEW:
    process_input(KW_NEW);
    process_input(ID);
    break;
  case OPEN_PAREN:
    f_L_EXP();
    f_OPT_EXP();
    break;
  case KW_DEREF:
    f_L_EXP();
    f_OPT_EXP();
    break;
  case ID:
    f_L_EXP();
    f_OPT_EXP();
    break;
  default:
    error();
  }
}
void f_VAR() {
  switch (token) {
  case OPEN_PAREN:
    process_input(OPEN_PAREN);
    f_REC_VAR();
    process_input(CLOSE_PAREN);
    break;
  case KW_DEREF:
    f_NAMELESS_VAR();
    break;
  case ID:
    process_input(ID);
    f_NAME_VAR();
    break;
  default:
    error();
  }
}
void f_Z_PROC_DECL() {
  switch (token) {
  case KW_IN:
    break;
  case KW_SEMICOLUMN:
    process_input(KW_SEMICOLUMN);
    f_Y_PROC_DECL();
    break;
  default:
    error();
  }
}
void f_STMT_LIST() {
  switch (token) {
  case KW_RETURN:
    f_STMT();
    f_T_STMT_LIST();
    break;
  case KW_OD:
    break;
  case KW_ELSE:
    break;
  case KW_DO:
    f_STMT();
    f_T_STMT_LIST();
    break;
  case KW_FI:
    break;
  case KW_IF:
    f_STMT();
    f_T_STMT_LIST();
    break;
  case KW_WHILE:
    f_STMT();
    f_T_STMT_LIST();
    break;
  case KW_END:
    break;
  case KW_DEREF:
    f_STMT();
    f_T_STMT_LIST();
    break;
  case ID:
    f_STMT();
    f_T_STMT_LIST();
    break;
  default:
    error();
  }
}
void f_LU_EXP() {
  switch (token) {
  case KW_TRUE:
    f_R_EXP();
    f_LU2_EXP();
    break;
  case KW_FALSE:
    f_R_EXP();
    f_LU2_EXP();
    break;
  case KW_NULL:
    f_R_EXP();
    f_LU2_EXP();
    break;
  case STRING_LITERAL:
    f_R_EXP();
    f_LU2_EXP();
    break;
  case INT_LITERAL:
    f_R_EXP();
    f_LU2_EXP();
    break;
  case FLOAT_LITERAL:
    f_R_EXP();
    f_LU2_EXP();
    break;
  case OP_NOT:
    f_R_EXP();
    f_LU2_EXP();
    break;
  case OPEN_PAREN:
    f_R_EXP();
    f_LU2_EXP();
    break;
  case KW_DEREF:
    f_R_EXP();
    f_LU2_EXP();
    break;
  case ID:
    f_R_EXP();
    f_LU2_EXP();
    break;
  default:
    error();
  }
}
void f_S() {
  switch (token) {
  case KW_PROGRAM:
    f_PROGRAM();
    break;
  default:
    error();
  }
}
void f_U_PROGRAM() {
  switch (token) {
  case KW_SEMICOLUMN:
    process_input(KW_SEMICOLUMN);
    f_DECL();
    f_U_PROGRAM();
    break;
  case KW_END:
    break;
  default:
    error();
  }
}
void f_PROC_DECL() {
  switch (token) {
  case KW_PROCEDURE:
    process_input(KW_PROCEDURE);
    process_input(ID);
    process_input(OPEN_PAREN);
    f_T_PROC_DECL();
    process_input(CLOSE_PAREN);
    f_U_PROC_DECL();
    process_input(KW_BEGIN);
    f_V_PROC_DECL();
    f_STMT_LIST();
    process_input(KW_END);
    break;
  default:
    error();
  }
}
void f_PROGRAM() {
  switch (token) {
  case KW_PROGRAM:
    process_input(KW_PROGRAM);
    process_input(ID);
    process_input(KW_BEGIN);
    f_T_PROGRAM();
    process_input(KW_END);
    break;
  default:
    error();
  }
}
void f_Y_PROC_DECL() {
  switch (token) {
  case KW_STRUCT:
    f_DECL();
    f_Z_PROC_DECL();
    break;
  case KW_IN:
    break;
  case KW_PROCEDURE:
    f_DECL();
    f_Z_PROC_DECL();
    break;
  case KW_VAR:
    f_DECL();
    f_Z_PROC_DECL();
    break;
  default:
    error();
  }
}
void f_U_VAR_DECL() {
  switch (token) {
  case KW_IN:
    break;
  case OP_ASSIGN:
    process_input(OP_ASSIGN);
    f_EXP();
    break;
  case KW_SEMICOLUMN:
    break;
  case KW_END:
    break;
  default:
    error();
  }
}
void f_ASSIGN_STMT() {
  switch (token) {
  case KW_DEREF:
    f_NAMELESS_ASSIGN_STMT();
    break;
  case ID:
    process_input(ID);
    f_NAME_ASSIGN_STMT();
    break;
  default:
    error();
  }
}
void f_POW_EXP() {
  switch (token) {
  case KW_TRUE:
    f_FIM_EXP();
    f_POW_EXP2();
    break;
  case KW_FALSE:
    f_FIM_EXP();
    f_POW_EXP2();
    break;
  case KW_NULL:
    f_FIM_EXP();
    f_POW_EXP2();
    break;
  case STRING_LITERAL:
    f_FIM_EXP();
    f_POW_EXP2();
    break;
  case INT_LITERAL:
    f_FIM_EXP();
    f_POW_EXP2();
    break;
  case FLOAT_LITERAL:
    f_FIM_EXP();
    f_POW_EXP2();
    break;
  case OP_NOT:
    f_FIM_EXP();
    f_POW_EXP2();
    break;
  case OPEN_PAREN:
    f_FIM_EXP();
    f_POW_EXP2();
    break;
  case KW_DEREF:
    f_FIM_EXP();
    f_POW_EXP2();
    break;
  case ID:
    f_FIM_EXP();
    f_POW_EXP2();
    break;
  default:
    error();
  }
}
void f_T_PROGRAM() {
  switch (token) {
  case KW_STRUCT:
    f_DECL();
    f_U_PROGRAM();
    break;
  case KW_PROCEDURE:
    f_DECL();
    f_U_PROGRAM();
    break;
  case KW_VAR:
    f_DECL();
    f_U_PROGRAM();
    break;
  case KW_END:
    break;
  default:
    error();
  }
}
void f_T_REC_DECL() {
  switch (token) {
  case CLOSE_CURLY:
    break;
  case ID:
    f_PARAMFIELD_DECL();
    f_U_REC_DECL();
    break;
  default:
    error();
  }
}
void f_V_PROC_DECL() {
  switch (token) {
  case KW_RETURN:
    break;
  case KW_DO:
    break;
  case KW_IF:
    break;
  case KW_STRUCT:
    f_Y_PROC_DECL();
    process_input(KW_IN);
    break;
  case KW_IN:
    f_Y_PROC_DECL();
    process_input(KW_IN);
    break;
  case KW_PROCEDURE:
    f_Y_PROC_DECL();
    process_input(KW_IN);
    break;
  case KW_WHILE:
    break;
  case KW_END:
    break;
  case KW_DEREF:
    break;
  case KW_VAR:
    f_Y_PROC_DECL();
    process_input(KW_IN);
    break;
  case ID:
    break;
  default:
    error();
  }
}
void f_REC_DECL() {
  switch (token) {
  case KW_STRUCT:
    process_input(KW_STRUCT);
    process_input(ID);
    process_input(OPEN_CURLY);
    f_T_REC_DECL();
    process_input(CLOSE_CURLY);
    break;
  default:
    error();
  }
}
void f_POW_EXP2() {
  switch (token) {
  case KW_OD:
    break;
  case KW_ELSE:
    break;
  case KW_FI:
    break;
  case KW_TRUE:
    break;
  case KW_DO:
    break;
  case OP_SMALLER_OR_EQ:
    break;
  case STRING_LITERAL:
    break;
  case OP_SMALLER:
    break;
  case OP_GREATER:
    break;
  case KW_COMMA:
    break;
  case CLOSE_PAREN:
    break;
  case KW_END:
    break;
  case OP_OR:
    break;
  case OP_EQUAL:
    break;
  case OP_AND:
    break;
  case OP_GREATER_OR_EQ:
    break;
  case KW_SEMICOLUMN:
    break;
  case ID:
    break;
  case KW_IN:
    break;
  case OP_NOT_EQUAL:
    break;
  case OPEN_PAREN:
    break;
  case OP_ADD:
    break;
  case OP_SUB:
    break;
  case OP_MULT:
    break;
  case KW_THEN:
    break;
  case KW_REF:
    break;
  case OP_DIV:
    break;
  case OP_NOT:
    break;
  case OP_EXP:
    process_input(OP_EXP);
    f_POW_EXP();
    break;
  case KW_DEREF:
    break;
  case KW_NEW:
    break;
  case FLOAT_LITERAL:
    break;
  case INT_LITERAL:
    break;
  case KW_NULL:
    break;
  case KW_FALSE:
    break;
  default:
    error();
  }
}
void f_NAME_CALL_STMT() {
  switch (token) {
  case OPEN_PAREN:
    process_input(OPEN_PAREN);
    f_T_CALL_STMT();
    process_input(CLOSE_PAREN);
    break;
  default:
    error();
  }
}
void f_X_PROC_DECL() {
  switch (token) {
  case KW_COMMA:
    process_input(KW_COMMA);
    f_PARAMFIELD_DECL();
    f_X_PROC_DECL();
    break;
  case CLOSE_PAREN:
    break;
  default:
    error();
  }
}
void f_VAR_DECL() {
  switch (token) {
  case KW_VAR:
    process_input(KW_VAR);
    process_input(ID);
    f_T_VAR_DECL();
    break;
  default:
    error();
  }
}
void f_L_EXP() {
  switch (token) {
  case KW_TRUE:
    f_LU_EXP();
    f_L2_EXP();
    break;
  case KW_FALSE:
    f_LU_EXP();
    f_L2_EXP();
    break;
  case KW_NULL:
    f_LU_EXP();
    f_L2_EXP();
    break;
  case STRING_LITERAL:
    f_LU_EXP();
    f_L2_EXP();
    break;
  case INT_LITERAL:
    f_LU_EXP();
    f_L2_EXP();
    break;
  case FLOAT_LITERAL:
    f_LU_EXP();
    f_L2_EXP();
    break;
  case OP_NOT:
    f_LU_EXP();
    f_L2_EXP();
    break;
  case OPEN_PAREN:
    f_LU_EXP();
    f_L2_EXP();
    break;
  case KW_DEREF:
    f_LU_EXP();
    f_L2_EXP();
    break;
  case ID:
    f_LU_EXP();
    f_L2_EXP();
    break;
  default:
    error();
  }
}
void f_STMT() {
  switch (token) {
  case KW_RETURN:
    f_RETURN_STMT();
    break;
  case KW_WHILE:
    f_WHILE_STMT();
    break;
  case KW_DO:
    f_DO_STMT();
    break;
  case KW_IF:
    f_IF_STMT();
    break;
  case KW_DEREF:
    f_NAMELESS_ASSIGN_STMT();
    break;
  case ID:
    process_input(ID);
    f_NAME_STMT();
    break;
  default:
    error();
  }
}
void f_T_VAR_DECL() {
  switch (token) {
  case OP_ASSIGN:
    process_input(OP_ASSIGN);
    f_EXP();
    break;
  case KW_COLUMN:
    process_input(KW_COLUMN);
    f_TYPE();
    f_U_VAR_DECL();
    break;
  default:
    error();
  }
}
void f_U_REC_DECL() {
  switch (token) {
  case CLOSE_CURLY:
    break;
  case KW_SEMICOLUMN:
    process_input(KW_SEMICOLUMN);
    f_PARAMFIELD_DECL();
    f_U_REC_DECL();
    break;
  default:
    error();
  }
}
void f_T_PROC_DECL() {
  switch (token) {
  case CLOSE_PAREN:
    break;
  case ID:
    f_PARAMFIELD_DECL();
    f_X_PROC_DECL();
    break;
  default:
    error();
  }
}
void f_AU_EXP() {
  switch (token) {
  case KW_TRUE:
    f_POW_EXP();
    f_AU2_EXP();
    break;
  case KW_FALSE:
    f_POW_EXP();
    f_AU2_EXP();
    break;
  case KW_NULL:
    f_POW_EXP();
    f_AU2_EXP();
    break;
  case STRING_LITERAL:
    f_POW_EXP();
    f_AU2_EXP();
    break;
  case INT_LITERAL:
    f_POW_EXP();
    f_AU2_EXP();
    break;
  case FLOAT_LITERAL:
    f_POW_EXP();
    f_AU2_EXP();
    break;
  case OP_NOT:
    f_POW_EXP();
    f_AU2_EXP();
    break;
  case OPEN_PAREN:
    f_POW_EXP();
    f_AU2_EXP();
    break;
  case KW_DEREF:
    f_POW_EXP();
    f_AU2_EXP();
    break;
  case ID:
    f_POW_EXP();
    f_AU2_EXP();
    break;
  default:
    error();
  }
}
void f_A_EXP() {
  switch (token) {
  case KW_TRUE:
    f_AU_EXP();
    f_A2_EXP();
    break;
  case KW_FALSE:
    f_AU_EXP();
    f_A2_EXP();
    break;
  case KW_NULL:
    f_AU_EXP();
    f_A2_EXP();
    break;
  case STRING_LITERAL:
    f_AU_EXP();
    f_A2_EXP();
    break;
  case INT_LITERAL:
    f_AU_EXP();
    f_A2_EXP();
    break;
  case FLOAT_LITERAL:
    f_AU_EXP();
    f_A2_EXP();
    break;
  case OP_NOT:
    f_AU_EXP();
    f_A2_EXP();
    break;
  case OPEN_PAREN:
    f_AU_EXP();
    f_A2_EXP();
    break;
  case KW_DEREF:
    f_AU_EXP();
    f_A2_EXP();
    break;
  case ID:
    f_AU_EXP();
    f_A2_EXP();
    break;
  default:
    error();
  }
}
void f_WHILE_STMT() {
  switch (token) {
  case KW_WHILE:
    process_input(KW_WHILE);
    f_EXP();
    process_input(KW_DO);
    f_STMT_LIST();
    process_input(KW_OD);
    break;
  default:
    error();
  }
}
void f_A2_EXP() {
  switch (token) {
  case KW_OD:
    break;
  case KW_ELSE:
    break;
  case KW_DO:
    break;
  case OP_SMALLER_OR_EQ:
    break;
  case STRING_LITERAL:
    break;
  case OP_SMALLER:
    break;
  case OP_GREATER:
    break;
  case KW_COMMA:
    break;
  case KW_REF:
    break;
  case KW_THEN:
    break;
  case CLOSE_PAREN:
    break;
  case KW_END:
    break;
  case OP_OR:
    break;
  case OP_EQUAL:
    break;
  case OP_AND:
    break;
  case OP_GREATER_OR_EQ:
    break;
  case KW_SEMICOLUMN:
    break;
  case ID:
    break;
  case KW_IN:
    break;
  case OP_NOT_EQUAL:
    break;
  case OPEN_PAREN:
    break;
  case OP_ADD:
    process_input(OP_ADD);
    f_AU_EXP();
    f_A2_EXP();
    break;
  case OP_SUB:
    process_input(OP_SUB);
    f_AU_EXP();
    f_A2_EXP();
    break;
  case OP_NOT:
    break;
  case KW_DEREF:
    break;
  case KW_NEW:
    break;
  case FLOAT_LITERAL:
    break;
  case INT_LITERAL:
    break;
  case KW_NULL:
    break;
  case KW_FALSE:
    break;
  case KW_FI:
    break;
  case KW_TRUE:
    break;
  default:
    error();
  }
}
void f_AU2_EXP() {
  switch (token) {
  case KW_OD:
    break;
  case KW_ELSE:
    break;
  case KW_FI:
    break;
  case KW_DO:
    break;
  case OP_SMALLER_OR_EQ:
    break;
  case STRING_LITERAL:
    break;
  case OP_SMALLER:
    break;
  case OP_GREATER:
    break;
  case KW_COMMA:
    break;
  case CLOSE_PAREN:
    break;
  case KW_END:
    break;
  case OP_OR:
    break;
  case OP_EQUAL:
    break;
  case OP_AND:
    break;
  case OP_GREATER_OR_EQ:
    break;
  case KW_SEMICOLUMN:
    break;
  case ID:
    break;
  case KW_IN:
    break;
  case OP_NOT_EQUAL:
    break;
  case OPEN_PAREN:
    break;
  case OP_ADD:
    break;
  case OP_SUB:
    break;
  case OP_MULT:
    process_input(OP_MULT);
    f_POW_EXP();
    f_AU2_EXP();
    break;
  case KW_THEN:
    break;
  case KW_REF:
    break;
  case OP_DIV:
    process_input(OP_DIV);
    f_POW_EXP();
    f_AU2_EXP();
    break;
  case OP_NOT:
    break;
  case KW_DEREF:
    break;
  case KW_NEW:
    break;
  case FLOAT_LITERAL:
    break;
  case INT_LITERAL:
    break;
  case KW_NULL:
    break;
  case KW_FALSE:
    break;
  case KW_TRUE:
    break;
  default:
    error();
  }
}
void f_FIM_EXP() {
  switch (token) {
  case KW_TRUE:
    f_LITERAL();
    break;
  case KW_FALSE:
    f_LITERAL();
    break;
  case KW_NULL:
    f_LITERAL();
    break;
  case STRING_LITERAL:
    f_LITERAL();
    break;
  case INT_LITERAL:
    f_LITERAL();
    break;
  case FLOAT_LITERAL:
    f_LITERAL();
    break;
  case OP_NOT:
    process_input(OP_NOT);
    f_FIM_EXP();
    break;
  case OPEN_PAREN:
    process_input(OPEN_PAREN);
    f_EXP();
    process_input(CLOSE_PAREN);
    break;
  case KW_DEREF:
    f_DEREF_VAR();
    f_OPT_DOT_NAME();
    break;
  case ID:
    process_input(ID);
    f_OPT_DOT_NAME();
    break;
  default:
    error();
  }
}
void f_NAME_STMT() {
  switch (token) {
  case OPEN_PAREN:
    f_NAME_CALL_STMT();
    f_OPT_DOT_NAME_ASSIGN_EXP();
    break;
  case OP_ASSIGN:
    process_input(OP_ASSIGN);
    f_EXP();
    break;
  default:
    error();
  }
}
void f_REF_VAR() {
  switch (token) {
  case KW_REF:
    process_input(KW_REF);
    process_input(OPEN_PAREN);
    f_VAR();
    process_input(CLOSE_PAREN);
    break;
  default:
    error();
  }
}
void f_NO_PAREN_VAR() {
  switch (token) {
  case KW_DEREF:
    f_NAMELESS_VAR();
    break;
  case ID:
    process_input(ID);
    f_NAME_VAR();
    break;
  default:
    error();
  }
}
void f_DEREF_VAR() {
  switch (token) {
  case KW_DEREF:
    process_input(KW_DEREF);
    process_input(OPEN_PAREN);
    f_VAR();
    process_input(CLOSE_PAREN);
    break;
  default:
    error();
  }
}
void f_T_STMT_LIST() {
  switch (token) {
  case KW_OD:
    break;
  case KW_ELSE:
    break;
  case KW_FI:
    break;
  case KW_SEMICOLUMN:
    process_input(KW_SEMICOLUMN);
    f_STMT_LIST();
    break;
  case KW_END:
    break;
  default:
    error();
  }
}
void f_NAME_ASSIGN_STMT() {
  switch (token) {
  case OPEN_PAREN:
    f_NAME_VAR();
    process_input(OP_ASSIGN);
    f_EXP();
    break;
  case OP_ASSIGN:
    f_NAME_VAR();
    process_input(OP_ASSIGN);
    f_EXP();
    break;
  default:
    error();
  }
}
void f_REC_VAR() {
  switch (token) {
  case OPEN_PAREN:
    process_input(OPEN_PAREN);
    f_REC_VAR();
    process_input(CLOSE_PAREN);
    break;
  case KW_DEREF:
    f_DEREF_VAR();
    process_input(KW_DOT);
    process_input(ID);
    break;
  case ID:
    f_CALL_STMT();
    process_input(KW_DOT);
    process_input(ID);
    break;
  default:
    error();
  }
}
void f_NAMELESS_DEREF_VAR_VAR() {
  switch (token) {
  case KW_DOT:
    process_input(KW_DOT);
    process_input(ID);
    break;
  default:
    error();
  }
}
void f_TYPE() {
  switch (token) {
  case KW_BOOL:
    process_input(KW_BOOL);
    break;
  case KW_STRING:
    process_input(KW_STRING);
    break;
  case KW_REF:
    process_input(KW_REF);
    process_input(OPEN_PAREN);
    f_TYPE();
    process_input(CLOSE_PAREN);
    break;
  case KW_INT:
    process_input(KW_INT);
    break;
  case KW_FLOAT:
    process_input(KW_FLOAT);
    break;
  case ID:
    process_input(ID);
    break;
  default:
    error();
  }
}
void f_T_CALL_STMT() {
  switch (token) {
  case KW_TRUE:
    f_EXP();
    f_U_CALL_STMT();
    break;
  case INT_LITERAL:
    f_EXP();
    f_U_CALL_STMT();
    break;
  case FLOAT_LITERAL:
    f_EXP();
    f_U_CALL_STMT();
    break;
  case KW_NULL:
    f_EXP();
    f_U_CALL_STMT();
    break;
  case STRING_LITERAL:
    f_EXP();
    f_U_CALL_STMT();
    break;
  case KW_REF:
    f_EXP();
    f_U_CALL_STMT();
    break;
  case OP_NOT:
    f_EXP();
    f_U_CALL_STMT();
    break;
  case KW_FALSE:
    f_EXP();
    f_U_CALL_STMT();
    break;
  case KW_NEW:
    f_EXP();
    f_U_CALL_STMT();
    break;
  case CLOSE_PAREN:
    break;
  case OPEN_PAREN:
    f_EXP();
    f_U_CALL_STMT();
    break;
  case KW_DEREF:
    f_EXP();
    f_U_CALL_STMT();
    break;
  case ID:
    f_EXP();
    f_U_CALL_STMT();
    break;
  default:
    error();
  }
}
void f_NAMELESS_VAR() {
  switch (token) {
  case KW_DEREF:
    f_DEREF_VAR();
    process_input(KW_DOT);
    process_input(ID);
    break;
  default:
    error();
  }
}
void f_LITERAL() {
  switch (token) {
  case KW_TRUE:
    f_BOOL_LITERAL();
    break;
  case KW_FALSE:
    f_BOOL_LITERAL();
    break;
  case KW_NULL:
    process_input(KW_NULL);
    break;
  case STRING_LITERAL:
    process_input(STRING_LITERAL);
    break;
  case INT_LITERAL:
    process_input(INT_LITERAL);
    break;
  case FLOAT_LITERAL:
    process_input(FLOAT_LITERAL);
    break;
  default:
    error();
  }
}
void f_DECL() {
  switch (token) {
  case KW_STRUCT:
    f_REC_DECL();
    break;
  case KW_PROCEDURE:
    f_PROC_DECL();
    break;
  case KW_VAR:
    f_VAR_DECL();
    break;
  default:
    error();
  }
}
void f_T_IF_STMT() {
  switch (token) {
  case KW_ELSE:
    process_input(KW_ELSE);
    f_STMT_LIST();
    break;
  case KW_FI:
    break;
  default:
    error();
  }
}
void f_R2_EXP() {
  switch (token) {
  case KW_OD:
    break;
  case STRING_LITERAL:
    break;
  case OP_SMALLER:
    process_input(OP_SMALLER);
    f_A_EXP();
    f_R2_EXP();
    break;
  case OPEN_PAREN:
    break;
  case OP_GREATER:
    process_input(OP_GREATER);
    f_A_EXP();
    f_R2_EXP();
    break;
  case KW_COMMA:
    break;
  case KW_REF:
    break;
  case KW_THEN:
    break;
  case CLOSE_PAREN:
    break;
  case KW_END:
    break;
  case OP_OR:
    break;
  case OP_EQUAL:
    process_input(OP_EQUAL);
    f_A_EXP();
    f_R2_EXP();
    break;
  case OP_AND:
    break;
  case OP_GREATER_OR_EQ:
    process_input(OP_GREATER_OR_EQ);
    f_A_EXP();
    f_R2_EXP();
    break;
  case KW_ELSE:
    break;
  case KW_SEMICOLUMN:
    break;
  case ID:
    break;
  case KW_IN:
    break;
  case OP_NOT_EQUAL:
    process_input(OP_NOT_EQUAL);
    f_A_EXP();
    f_R2_EXP();
    break;
  case OP_NOT:
    break;
  case KW_DEREF:
    break;
  case KW_NEW:
    break;
  case FLOAT_LITERAL:
    break;
  case INT_LITERAL:
    break;
  case KW_NULL:
    break;
  case KW_FALSE:
    break;
  case KW_FI:
    break;
  case KW_TRUE:
    break;
  case OP_SMALLER_OR_EQ:
    process_input(OP_SMALLER_OR_EQ);
    f_A_EXP();
    f_R2_EXP();
    break;
  case KW_DO:
    break;
  default:
    error();
  }
}
void f_BOOL_LITERAL() {
  switch (token) {
  case KW_TRUE:
    process_input(KW_TRUE);
    break;
  case KW_FALSE:
    process_input(KW_FALSE);
    break;
  default:
    error();
  }
}
void f_OPT_DOT_NAME_ASSIGN_EXP() {
  switch (token) {
  case KW_OD:
    break;
  case KW_ELSE:
    break;
  case KW_FI:
    break;
  case KW_DOT:
    process_input(KW_DOT);
    process_input(ID);
    process_input(OP_ASSIGN);
    f_EXP();
    break;
  case KW_SEMICOLUMN:
    break;
  case KW_END:
    break;
  default:
    error();
  }
}
void f_OPT_DOT_NAME() {
  switch (token) {
  case KW_OD:
    break;
  case KW_ELSE:
    break;
  case KW_FI:
    break;
  case KW_TRUE:
    break;
  case KW_FALSE:
    break;
  case KW_NULL:
    break;
  case KW_DO:
    break;
  case OP_SMALLER_OR_EQ:
    break;
  case STRING_LITERAL:
    break;
  case OP_SMALLER:
    break;
  case OP_ASSIGN:
    break;
  case OP_GREATER:
    break;
  case KW_COMMA:
    break;
  case CLOSE_PAREN:
    break;
  case KW_END:
    break;
  case OP_OR:
    break;
  case OP_EQUAL:
    break;
  case OP_AND:
    break;
  case OP_GREATER_OR_EQ:
    break;
  case KW_SEMICOLUMN:
    break;
  case ID:
    break;
  case KW_IN:
    break;
  case OP_NOT_EQUAL:
    break;
  case OPEN_PAREN:
    break;
  case OP_ADD:
    break;
  case OP_SUB:
    break;
  case OP_MULT:
    break;
  case KW_THEN:
    break;
  case KW_REF:
    break;
  case OP_DIV:
    break;
  case OP_NOT:
    break;
  case OP_EXP:
    break;
  case KW_DEREF:
    break;
  case KW_DOT:
    process_input(KW_DOT);
    process_input(ID);
    break;
  case KW_NEW:
    break;
  case FLOAT_LITERAL:
    break;
  case INT_LITERAL:
    break;
  default:
    error();
  }
}
void f_NAMELESS_ASSIGN_STMT() {
  switch (token) {
  case KW_DEREF:
    f_DEREF_VAR();
    f_OPT_DOT_NAME();
    process_input(OP_ASSIGN);
    f_EXP();
    break;
  default:
    error();
  }
}
void f_U_PROC_DECL() {
  switch (token) {
  case KW_COLUMN:
    process_input(KW_COLUMN);
    f_TYPE();
    break;
  case KW_BEGIN:
    break;
  default:
    error();
  }
}
void f_IF_STMT() {
  switch (token) {
  case KW_IF:
    process_input(KW_IF);
    f_EXP();
    process_input(KW_THEN);
    f_STMT_LIST();
    f_T_IF_STMT();
    process_input(KW_FI);
    break;
  default:
    error();
  }
}
void f_CALL_STMT() {
  switch (token) {
  case ID:
    process_input(ID);
    f_NAME_CALL_STMT();
    break;
  default:
    error();
  }
}
