#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <vector>

#include "../build/lex.yy.cc"
#include "../build/parser.tab.hpp"
#include "non_terminals.h"

#define SymbolType int
#define SymbolRecInputType std::pair<SymbolType, YYSTYPE>

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

bool LL_rec(std::stack<SymbolType> stack, std::queue<SymbolRecInputType> input);
std::vector<std::vector<SymbolType>> &consult_rules(SymbolType symbol);
void init_rules();
SymbolType get_symbol_key(std::string symbol);
// Since LL_rec performs backtracking, the input must be read and saved at the
// beginning
std::queue<SymbolRecInputType> read_rec_input();

bool is_terminal(SymbolType symbol);
void error(SymbolType symbol, const YYSTYPE &input_yylval = yylval);
void print_usage();

int main(int argc, char *argv[]) {
  if (argc != 2) {
    print_usage();
    return 1;
  }

  // Initializing LL stack
  std::stack<SymbolType> stack;
  stack.push(END);
  stack.push(PROGRAM); // Start symbol

  bool sucessful_parse;
  if (std::strcmp(argv[1], "-table") == 0) {
    init_table();
    sucessful_parse = LL_table(stack);
  } else if (std::strcmp(argv[1], "-rec") == 0) {
    init_rules();
    std::queue<SymbolRecInputType> input_symbols = read_rec_input();
    sucessful_parse = LL_rec(stack, input_symbols);
  } else {
    print_usage();
    return 1;
  }

  if (sucessful_parse) {
    std::cout << "Input belongs to grammar" << std::endl;
  } else {
    std::cout << "Input doesn't belong to grammar" << std::endl;
  }

  return 0;
}

bool LL_table(std::stack<SymbolType> &stack) {
  SymbolType curr_input_symbol;
  bool must_read_input_symbol = true;
  bool reached_input_end = false;

  while (!stack.empty() && !reached_input_end) {
    SymbolType top_stack_symbol = stack.top();
    if (must_read_input_symbol) {
      SymbolType symbol = yylex();
      must_read_input_symbol = false;
      if (symbol == 0) {
        symbol = END;
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

void init_table() {
  // TODO
}

bool LL_rec(std::stack<SymbolType> stack,
            std::queue<SymbolRecInputType> input_symbols) {

  if (stack.empty() || input_symbols.empty()) {
    return stack.empty() && input_symbols.empty();
  }

  auto [curr_input_symbol, curr_yylval] = input_symbols.front();
  SymbolType top_stack_symbol = stack.top();

  if (is_terminal(top_stack_symbol)) {
    if (top_stack_symbol == curr_input_symbol) {
      stack.pop();
      input_symbols.pop();
      return LL_rec(stack, input_symbols);
    } else {
      return false;
    }
  }

  for (const std::vector<SymbolType> &rule : consult_rules(top_stack_symbol)) {
    // Try each of those rules hopping for a match
    std::stack<SymbolType> stack_cp = stack;
    stack_cp.pop();
    for (SymbolType s : rule) {
      stack_cp.push(s);
    }
    if (LL_rec(stack_cp, input_symbols)) {
      return true;
    }
  }
  error(curr_input_symbol, curr_yylval);
  return false;
}

std::vector<std::vector<SymbolType>> &consult_rules(SymbolType symbol) {
  assert(symbol >= 0 && symbol < NUMBER_OF_NON_TERMINALS);
  return rules[symbol];
}

void init_rules() {
  std::ifstream input_file("left_recursive_grammar.txt");
  std::string line;
  while (std::getline(input_file, line)) {
    std::istringstream iss(line);
    std::string symbol;
    iss >> symbol;
    if (symbol == "#")
      continue;

    int non_terminal_key = get_symbol_key(symbol);
    iss >> symbol;
    assert(symbol == "::=");

    std::vector<SymbolType> rule_symbols;
    while (iss >> symbol)
      rule_symbols.push_back(get_symbol_key(symbol));

    rules[non_terminal_key].push_back(rule_symbols);
  }
}

SymbolType get_symbol_key(std::string symbol) {
  if (symbol == "PROGRAM")
    return PROGRAM;
  else if (symbol == "KW_PROGRAM")
    return KW_PROGRAM;
  else if (symbol == "ID")
    return ID;
  else if (symbol == "KW_BEGIN")
    return KW_BEGIN;
  else if (symbol == "T_PROGRAM")
    return T_PROGRAM;
  else if (symbol == "KW_END")
    return KW_END;
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
  else if (symbol == "KW_VAR")
    return KW_VAR;
  else if (symbol == "T_VAR_DECL")
    return T_VAR_DECL;
  else if (symbol == "KW_COLUMN")
    return KW_COLUMN;
  else if (symbol == "TYPE")
    return TYPE;
  else if (symbol == "OP_ASSIGN")
    return OP_ASSIGN;
  else if (symbol == "EXP")
    return EXP;
  else if (symbol == "U_VAR_DECL")
    return U_VAR_DECL;
  else if (symbol == "KW_PROCEDURE")
    return KW_PROCEDURE;
  else if (symbol == "OPEN_PAREN")
    return OPEN_PAREN;
  else if (symbol == "T_PROC_DECL")
    return T_PROC_DECL;
  else if (symbol == "CLOSE_PAREN")
    return CLOSE_PAREN;
  else if (symbol == "U_PROC_DECL")
    return U_PROC_DECL;
  else if (symbol == "V_PROC_DECL")
    return V_PROC_DECL;
  else if (symbol == "STMT_LIST")
    return STMT_LIST;
  else if (symbol == "PARAMFIELD_DECL")
    return PARAMFIELD_DECL;
  else if (symbol == "X_PROC_DECL")
    return X_PROC_DECL;
  else if (symbol == "KW_COMMA")
    return KW_COMMA;
  else if (symbol == "KW_IN")
    return KW_IN;
  else if (symbol == "Y_PROC_DECL")
    return Y_PROC_DECL;
  else if (symbol == "Z_PROC_DECL")
    return Z_PROC_DECL;
  else if (symbol == "KW_SEMICOLUMN")
    return KW_SEMICOLUMN;
  else if (symbol == "KW_STRUCT")
    return KW_STRUCT;
  else if (symbol == "OPEN_CURLY")
    return OPEN_CURLY;
  else if (symbol == "T_REC_DECL")
    return T_REC_DECL;
  else if (symbol == "CLOSE_CURLY")
    return CLOSE_CURLY;
  else if (symbol == "U_REC_DECL")
    return U_REC_DECL;
  else if (symbol == "T_STMT_LIST")
    return T_STMT_LIST;
  else if (symbol == "OPT_EXP")
    return OPT_EXP;
  else if (symbol == "L_EXP")
    return L_EXP;
  else if (symbol == "KW_NEW")
    return KW_NEW;
  else if (symbol == "REF_VAR")
    return REF_VAR;
  else if (symbol == "LU_EXP")
    return LU_EXP;
  else if (symbol == "L2_EXP")
    return L2_EXP;
  else if (symbol == "OP_OR")
    return OP_OR;
  else if (symbol == "R_EXP")
    return R_EXP;
  else if (symbol == "LU2_EXP")
    return LU2_EXP;
  else if (symbol == "OP_AND")
    return OP_AND;
  else if (symbol == "A_EXP")
    return A_EXP;
  else if (symbol == "R2_EXP")
    return R2_EXP;
  else if (symbol == "OP_SMALLER")
    return OP_SMALLER;
  else if (symbol == "OP_SMALLER_OR_EQ")
    return OP_SMALLER_OR_EQ;
  else if (symbol == "OP_GREATER")
    return OP_GREATER;
  else if (symbol == "OP_GREATER_OR_EQ")
    return OP_GREATER_OR_EQ;
  else if (symbol == "OP_EQUAL")
    return OP_EQUAL;
  else if (symbol == "OP_NOT_EQUAL")
    return OP_NOT_EQUAL;
  else if (symbol == "AU_EXP")
    return AU_EXP;
  else if (symbol == "A2_EXP")
    return A2_EXP;
  else if (symbol == "OP_ADD")
    return OP_ADD;
  else if (symbol == "OP_SUB")
    return OP_SUB;
  else if (symbol == "POW_EXP")
    return POW_EXP;
  else if (symbol == "AU2_EXP")
    return AU2_EXP;
  else if (symbol == "OP_MULT")
    return OP_MULT;
  else if (symbol == "OP_DIV")
    return OP_DIV;
  else if (symbol == "FIM_EXP")
    return FIM_EXP;
  else if (symbol == "POW_EXP2")
    return POW_EXP2;
  else if (symbol == "OP_EXP")
    return OP_EXP;
  else if (symbol == "LITERAL")
    return LITERAL;
  else if (symbol == "OP_NOT")
    return OP_NOT;
  else if (symbol == "CLOSE_PAREN")
    return CLOSE_PAREN;
  else if (symbol == "DEREF_VAR")
    return DEREF_VAR;
  else if (symbol == "OPT_DOT_NAME")
    return OPT_DOT_NAME;
  else if (symbol == "KW_REF")
    return KW_REF;
  else if (symbol == "VAR")
    return VAR;
  else if (symbol == "KW_DEREF")
    return KW_DEREF;
  else if (symbol == "REC_VAR")
    return REC_VAR;
  else if (symbol == "KW_DOT")
    return KW_DOT;
  else if (symbol == "CALL_STMT")
    return CALL_STMT;
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
  else if (symbol == "FLOAT_LITERAL")
    return FLOAT_LITERAL;
  else if (symbol == "INT_LITERAL")
    return INT_LITERAL;
  else if (symbol == "STRING_LITERAL")
    return STRING_LITERAL;
  else if (symbol == "BOOL_LITERAL")
    return BOOL_LITERAL;
  else if (symbol == "KW_NULL")
    return KW_NULL;
  else if (symbol == "KW_FALSE")
    return KW_FALSE;
  else if (symbol == "KW_TRUE")
    return KW_TRUE;
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
  else if (symbol == "DO_STMT")
    return DO_STMT;
  else if (symbol == "NAME_STMT")
    return NAME_STMT;
  else if (symbol == "NAME_CALL_STMT")
    return NAME_CALL_STMT;
  else if (symbol == "OPT_DOT_NAME_ASSIGN_EXP")
    return OPT_DOT_NAME_ASSIGN_EXP;
  else if (symbol == "ASSIGN_STMT")
    return ASSIGN_STMT;
  else if (symbol == "NAME_ASSIGN_STMT")
    return NAME_ASSIGN_STMT;
  else if (symbol == "KW_IF")
    return KW_IF;
  else if (symbol == "KW_THEN")
    return KW_THEN;
  else if (symbol == "T_IF_STMT")
    return T_IF_STMT;
  else if (symbol == "KW_FI")
    return KW_FI;
  else if (symbol == "KW_ELSE")
    return KW_ELSE;
  else if (symbol == "KW_WHILE")
    return KW_WHILE;
  else if (symbol == "KW_DO")
    return KW_DO;
  else if (symbol == "KW_OD")
    return KW_OD;
  else if (symbol == "KW_RETURN")
    return KW_RETURN;
  else if (symbol == "T_CALL_STMT")
    return T_CALL_STMT;
  else if (symbol == "U_CALL_STMT")
    return U_CALL_STMT;
  else if (symbol == "DO_STMT_LIST")
    return DO_STMT_LIST;
  else if (symbol == "KW_EXIT")
    return KW_EXIT;
  else if (symbol == "KW_WHEN")
    return KW_WHEN;
  else if (symbol == "KW_FLOAT")
    return KW_FLOAT;
  else if (symbol == "KW_INT")
    return KW_INT;
  else if (symbol == "KW_STRING")
    return KW_STRING;
  else if (symbol == "KW_BOOL")
    return KW_BOOL;
  else {
    assert(false && "Trying to get a key for an invalid symbol");
  }

  return 0;
}

std::queue<SymbolRecInputType> read_rec_input() {
  std::queue<SymbolRecInputType> input_symbols;
  SymbolType symbol;
  while ((symbol = yylex()) != 0) {
    input_symbols.push({symbol, yylval});
  }
  return input_symbols;
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
  std::cout << "Error at line " << line << "and at column " << column
            << std::endl;
}

void print_usage() {
  std::cout << "Missing or invalid command line argument! Must be -table or "
               "-rec, representing the LL algorithm to be used"
            << std::endl;
}
