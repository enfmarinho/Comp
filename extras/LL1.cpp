#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

#include "../build/lex.yy.cc"
#include "../build/parser.tab.hpp"
#include "non_terminals.h"

#define INPUT_FILE "left_recursive_table.csv"
#define SymbolType int

// Global variables
YYSTYPE yylval; // Used be Flex
std::vector<SymbolType> table[NUMBER_OF_NON_TERMINALS][NUMBER_OF_TERMINALS];

// 1d for the non-terminal symbols, 2d for each rule of the symbol, 3d for each
// symbol of the rule
std::vector<std::vector<SymbolType>> rules[NUMBER_OF_NON_TERMINALS];

// Functions signatures
bool LL_table(std::stack<SymbolType> &stack);
std::vector<SymbolType> &consult_table(SymbolType non_terminal,
                                       SymbolType terminal);
void init_table();
bool is_terminal(SymbolType symbol);
void error(SymbolType symbol, const YYSTYPE &input_yylval = yylval);
SymbolType get_symbol_key(std::string symbol);

int main(int argc, char *argv[]) {
  init_table();

  // Initializing LL stack
  std::stack<SymbolType> stack;
  stack.push(END);
  stack.push(PROGRAM); // Start symbol

  if (LL_table(stack))
    std::cout << "Input belongs to grammar" << std::endl;
  else
    std::cout << "Input doesn't belong to grammar" << std::endl;

  return 0;
}

bool LL_table(std::stack<SymbolType> &stack) {
  SymbolType curr_input_symbol;
  bool must_read_input_symbol = true;
  bool reached_input_end = false;

  while (!stack.empty() && !reached_input_end) {
    SymbolType top_stack_symbol = stack.top();
    if (must_read_input_symbol) {
      curr_input_symbol = yylex();
      must_read_input_symbol = false;
      if (curr_input_symbol == 0) {
        curr_input_symbol = END;
        reached_input_end = true;
      }
    }

    if (is_terminal(top_stack_symbol)) {
      if (top_stack_symbol == curr_input_symbol) {
        stack.pop();
        must_read_input_symbol = true;
      } else {
        error(curr_input_symbol);
        break;
      }
    } else if (!consult_table(top_stack_symbol, curr_input_symbol)
                    .empty()) { // If there is a relevant rule associated to the
                                // non-terminal symbol at the top of the stack
      stack.pop();
      for (SymbolType t : consult_table(top_stack_symbol, curr_input_symbol)) {
        if (t != EMPTY) { // Add symbols in table to the stack, except when
                          // symbol is empty
          stack.push(t);
        }
      }
    } else {
      error(curr_input_symbol);
      break;
    }
  }

  return reached_input_end && stack.empty();
}

std::vector<SymbolType> &consult_table(SymbolType non_terminal,
                                       SymbolType terminal) {
  terminal = terminal - EMPTY;
  assert(non_terminal >= 0 && non_terminal < NUMBER_OF_NON_TERMINALS &&
         "Try to index Table with an out of bound index");
  assert(terminal >= 0 && terminal < NUMBER_OF_TERMINALS &&
         "Try to index Table with an out of bound index");
  return table[non_terminal][terminal];
}

// Returns true if read "/n"
bool get_next_csv_value(std::ifstream &file_in, std::string &value) {
  value = "";
  char c = file_in.get();
  while (c != '\n' && c != ',' && !file_in.eof()) {
    value.push_back(c);
    c = file_in.get();
  }
  return c == '\n';
}

void ignore_line(std::ifstream &file_in) {
  std::string garbage;
  while (!get_next_csv_value(file_in, garbage)) {
  }
}

void init_table() {
  std::ifstream file_in(INPUT_FILE);
  std::string token;

  std::vector<std::string> terminal_symbols;
  get_next_csv_value(file_in, token); // Discard first value
  while (!get_next_csv_value(file_in, token)) {
    assert(!token.empty());
    terminal_symbols.push_back(token);
  }
  // terminal_symbols.push_back(token);
  terminal_symbols.push_back("kw_bool"); // Hard fix

  std::string non_terminal_symbol;
  while (!file_in.eof() && non_terminal_symbol != "TYPE") {
    get_next_csv_value(file_in, non_terminal_symbol);
    int non_terminal_symbol_key = get_symbol_key(non_terminal_symbol);

    for (int i = 0; i < terminal_symbols.size(); ++i) {
      std::string table_value;
      get_next_csv_value(file_in, table_value);

      if (table_value.empty() || table_value.size() == 1)
        continue;

      std::istringstream iss(table_value);
      iss >> token;
      assert(token == non_terminal_symbol);
      iss >> token;
      assert(token == "::=");

      while (iss >> token) {
        if (token == "ε")
          token = "empty";
        else if (token == "$")
          continue;

        consult_table(non_terminal_symbol_key,
                      get_symbol_key(terminal_symbols[i]))
            .push_back(get_symbol_key(token));
      }
    }
    if (!file_in.eof())
      ignore_line(file_in);
  }
}

bool is_terminal(SymbolType symbol) { return symbol >= EMPTY; }

void error(SymbolType symbol, const YYSTYPE &input_yylval) {
  int line, column;
  if (symbol == INT_LITERAL) {
    line = input_yylval.int_value.line;
    column = input_yylval.int_value.column;
  } else if (symbol == FLOAT_LITERAL) {
    line = input_yylval.float_value.line;
    column = input_yylval.float_value.column;
  } else if (symbol == STRING_LITERAL) {
    line = input_yylval.string_value.line;
    column = input_yylval.string_value.column;
  } else if (symbol == ID) {
    line = input_yylval.id.line;
    column = input_yylval.id.column;
  } else {
    line = input_yylval.general_values.line;
    column = input_yylval.general_values.column;
  }
  std::cout << "Error at line " << line << " and at column " << column
            << std::endl;
}
SymbolType get_symbol_key(std::string symbol) {
  // Non terminals symbols
  if (symbol == "PROGRAM")
    return PROGRAM;
  else if (symbol == "T_PROGRAM")
    return T_PROGRAM;
  else if (symbol == "DECL")
    return DECL;
  else if (symbol == "U_PROGRAM")
    return U_PROGRAM;
  else if (symbol == "VAR_DECL")
    return VAR_DECL;
  else if (symbol == "PROC_DECL")
    return PROC_DECL;
  else if (symbol == "REC_DECL")
    return REC_DECL;
  else if (symbol == "T_VAR_DECL")
    return T_VAR_DECL;
  else if (symbol == "U_VAR_DECL")
    return U_VAR_DECL;
  else if (symbol == "T_PROC_DECL")
    return T_PROC_DECL;
  else if (symbol == "X_PROC_DECL")
    return X_PROC_DECL;
  else if (symbol == "U_PROC_DECL")
    return U_PROC_DECL;
  else if (symbol == "V_PROC_DECL")
    return V_PROC_DECL;
  else if (symbol == "Y_PROC_DECL")
    return Y_PROC_DECL;
  else if (symbol == "Z_PROC_DECL")
    return Z_PROC_DECL;
  else if (symbol == "T_REC_DECL")
    return T_REC_DECL;
  else if (symbol == "U_REC_DECL")
    return U_REC_DECL;
  else if (symbol == "PARAMFIELD_DECL")
    return PARAMFIELD_DECL;
  else if (symbol == "STMT_LIST")
    return STMT_LIST;
  else if (symbol == "T_STMT_LIST")
    return T_STMT_LIST;
  else if (symbol == "OPT_EXP")
    return OPT_EXP;
  else if (symbol == "EXP")
    return EXP;
  else if (symbol == "L_EXP")
    return L_EXP;
  else if (symbol == "LU_EXP")
    return LU_EXP;
  else if (symbol == "L2_EXP")
    return L2_EXP;
  else if (symbol == "R_EXP")
    return R_EXP;
  else if (symbol == "LU2_EXP")
    return LU2_EXP;
  else if (symbol == "A_EXP")
    return A_EXP;
  else if (symbol == "R2_EXP")
    return R2_EXP;
  else if (symbol == "AU_EXP")
    return AU_EXP;
  else if (symbol == "A2_EXP")
    return A2_EXP;
  else if (symbol == "POW_EXP")
    return POW_EXP;
  else if (symbol == "AU2_EXP")
    return AU2_EXP;
  else if (symbol == "FIM_EXP")
    return FIM_EXP;
  else if (symbol == "POW_EXP2")
    return POW_EXP2;
  else if (symbol == "REF_VAR")
    return REF_VAR;
  else if (symbol == "DEREF_VAR")
    return DEREF_VAR;
  else if (symbol == "VAR")
    return VAR;
  else if (symbol == "REC_VAR")
    return REC_VAR;
  else if (symbol == "NAMELESS_VAR")
    return NAMELESS_VAR;
  else if (symbol == "NAME_VAR")
    return NAME_VAR;
  else if (symbol == "NAME_CALL_STMT")
    return NAME_CALL_STMT;
  else if (symbol == "NAMELESS_DEREF_VAR_VAR")
    return NAMELESS_DEREF_VAR_VAR;
  else if (symbol == "NO_PAREN_VAR")
    return NO_PAREN_VAR;
  else if (symbol == "LITERAL")
    return LITERAL;
  else if (symbol == "BOOL_LITERAL")
    return BOOL_LITERAL;
  else if (symbol == "STMT")
    return STMT;
  else if (symbol == "IF_STMT")
    return IF_STMT;
  else if (symbol == "WHILE_STMT")
    return WHILE_STMT;
  else if (symbol == "RETURN_STMT")
    return RETURN_STMT;
  else if (symbol == "NAMELESS_ASSIGN_STMT")
    return NAMELESS_ASSIGN_STMT;
  else if (symbol == "NAME_STMT")
    return NAME_STMT;
  else if (symbol == "OPT_DOT_NAME_ASSIGN_EXP")
    return OPT_DOT_NAME_ASSIGN_EXP;
  else if (symbol == "OPT_DOT_NAME")
    return OPT_DOT_NAME;
  else if (symbol == "CALL_STMT")
    return CALL_STMT;
  else if (symbol == "ASSIGN_STMT")
    return ASSIGN_STMT;
  else if (symbol == "NAME_ASSIGN_STMT")
    return NAME_ASSIGN_STMT;
  else if (symbol == "T_IF_STMT")
    return T_IF_STMT;
  else if (symbol == "T_CALL_STMT")
    return T_CALL_STMT;
  else if (symbol == "U_CALL_STMT")
    return U_CALL_STMT;
  else if (symbol == "DO_STMT")
    return DO_STMT;
  else if (symbol == "DO_STMT_LIST")
    return DO_STMT_LIST;
  else if (symbol == "bool_literal")
    return BOOL_LITERAL;
  else if (symbol == "TYPE")
    return TYPE;
  else if (symbol == "S")
    return S;

  // Terminals symbols
  else if (symbol == "id")
    return ID;
  else if (symbol == "kw_begin")
    return KW_BEGIN;
  else if (symbol == "kw_end")
    return KW_END;
  else if (symbol == "kw_program")
    return KW_PROGRAM;
  else if (symbol == "kw_begin")
    return KW_BEGIN;
  else if (symbol == "kw_end")
    return KW_END;
  else if (symbol == "kw_semicolumn")
    return KW_SEMICOLUMN;
  else if (symbol == "kw_var")
    return KW_VAR;
  else if (symbol == "kw_column")
    return KW_COLUMN;
  else if (symbol == "op_assign")
    return OP_ASSIGN;
  else if (symbol == "kw_procedure")
    return KW_PROCEDURE;
  else if (symbol == "open_paren")
    return OPEN_PAREN;
  else if (symbol == "close_paren")
    return CLOSE_PAREN;
  else if (symbol == "kw_comma")
    return KW_COMMA;
  else if (symbol == "kw_in")
    return KW_IN;
  else if (symbol == "kw_struct")
    return KW_STRUCT;
  else if (symbol == "open_curly")
    return OPEN_CURLY;
  else if (symbol == "close_curly")
    return CLOSE_CURLY;
  else if (symbol == "kw_new")
    return KW_NEW;
  else if (symbol == "op_or")
    return OP_OR;
  else if (symbol == "op_and")
    return OP_AND;
  else if (symbol == "op_smaller")
    return OP_SMALLER;
  else if (symbol == "op_smaller_or_eq")
    return OP_SMALLER_OR_EQ;
  else if (symbol == "op_greater")
    return OP_GREATER;
  else if (symbol == "op_greater_or_eq")
    return OP_GREATER_OR_EQ;
  else if (symbol == "op_equal")
    return OP_EQUAL;
  else if (symbol == "op_not_equal")
    return OP_NOT_EQUAL;
  else if (symbol == "op_add")
    return OP_ADD;
  else if (symbol == "op_sub")
    return OP_SUB;
  else if (symbol == "op_mult")
    return OP_MULT;
  else if (symbol == "op_div")
    return OP_DIV;
  else if (symbol == "op_exp")
    return OP_EXP;
  else if (symbol == "op_not")
    return OP_NOT;
  else if (symbol == "open_paren")
    return OPEN_PAREN;
  else if (symbol == "close_paren")
    return CLOSE_PAREN;
  else if (symbol == "kw_ref")
    return KW_REF;
  else if (symbol == "kw_deref")
    return KW_DEREF;
  else if (symbol == "kw_dot")
    return KW_DOT;
  else if (symbol == "float_literal")
    return FLOAT_LITERAL;
  else if (symbol == "int_literal")
    return INT_LITERAL;
  else if (symbol == "string_literal")
    return STRING_LITERAL;
  else if (symbol == "kw_null")
    return KW_NULL;
  else if (symbol == "kw_false")
    return KW_FALSE;
  else if (symbol == "kw_true")
    return KW_TRUE;
  else if (symbol == "kw_if")
    return KW_IF;
  else if (symbol == "kw_then")
    return KW_THEN;
  else if (symbol == "kw_fi")
    return KW_FI;
  else if (symbol == "kw_else")
    return KW_ELSE;
  else if (symbol == "kw_while")
    return KW_WHILE;
  else if (symbol == "kw_do")
    return KW_DO;
  else if (symbol == "kw_od")
    return KW_OD;
  else if (symbol == "kw_return")
    return KW_RETURN;
  else if (symbol == "kw_exit")
    return KW_EXIT;
  else if (symbol == "kw_when")
    return KW_WHEN;
  else if (symbol == "kw_float")
    return KW_FLOAT;
  else if (symbol == "kw_int")
    return KW_INT;
  else if (symbol == "kw_string")
    return KW_STRING;
  else if (symbol == "kw_bool")
    return KW_BOOL;
  else if (symbol == "empty")
    return EMPTY;
  else {
    std::cout << "failed for: " << symbol << std::endl;
    assert(false && "Trying to get a key for an invalid symbol");
  }

  return 0;
}
