#include <cassert>
#include <cstring>
#include <iostream>
#include <queue>
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
  rules[PROGRAM] = {{KW_PROGRAM, ID, KW_BEGIN, T_PROGRAM, KW_END}};
  rules[T_PROGRAM] = {{DECL, U_PROGRAM}, {EMPTY}};
  rules[U_PROGRAM] = {{KW_SEMICOLUMN, DECL, U_PROGRAM}, {EMPTY}};
  rules[DECL] = {{VAR_DECL}, {PROC_DECL}, {REC_DECL}};
  rules[VAR_DECL] = {{KW_VAR, ID, T_VAR_DECL}};
  rules[T_VAR_DECL] = {{KW_COLUMN, TYPE, U_VAR_DECL}, {OP_ASSIGN, EXP}};
  rules[U_VAR_DECL] = {{OP_ASSIGN, EXP}, {EMPTY}};
  rules[PROC_DECL] = {{KW_PROCEDURE, ID, OPEN_PAREN, T_PROC_DECL, CLOSE_PAREN,
                       U_PROC_DECL, KW_BEGIN, V_PROC_DECL, STMT_LIST, KW_END}};
  rules[T_PROC_DECL] = {{PARAMFIELD_DECL, X_PROC_DECL}, {EMPTY}};
  rules[X_PROC_DECL] = {{KW_COMMA, PARAMFIELD_DECL, X_PROC_DECL}, {EMPTY}};
  rules[U_PROC_DECL] = {{KW_COLUMN, TYPE}, {EMPTY}};
  rules[V_PROC_DECL] = {{Y_PROC_DECL, KW_IN}, {EMPTY}};
  rules[Y_PROC_DECL] = {{DECL, Z_PROC_DECL}, {EMPTY}};
  rules[Z_PROC_DECL] = {{KW_SEMICOLUMN, Y_PROC_DECL}, {EMPTY}};
  rules[REC_DECL] = {{KW_STRUCT, ID, OPEN_CURLY, T_REC_DECL, CLOSE_CURLY}};
  rules[T_REC_DECL] = {{PARAMFIELD_DECL, U_REC_DECL}, {EMPTY}};
  rules[U_REC_DECL] = {{KW_SEMICOLUMN, PARAMFIELD_DECL, U_REC_DECL}, {EMPTY}};
  rules[PARAMFIELD_DECL] = {{ID, KW_COLUMN, TYPE}};
  rules[STMT_LIST] = {{STMT, T_STMT_LIST}, {EMPTY}};
  rules[T_STMT_LIST] = {{KW_SEMICOLUMN, STMT_LIST}, {EMPTY}};
  rules[OPT_EXP] = {{EXP}, {EMPTY}};
  rules[EXP] = {{L_EXP, OPT_EXP}, {KW_NEW, ID}, {REF_VAR}};
  rules[L_EXP] = {{LU_EXP, L2_EXP}};
  rules[L2_EXP] = {{OP_OR, LU_EXP, L2_EXP}, {EMPTY}};
  rules[LU_EXP] = {{R_EXP, LU2_EXP}};
  rules[LU2_EXP] = {{OP_AND, R_EXP, LU2_EXP}, {EMPTY}};
  rules[R_EXP] = {{A_EXP, R2_EXP}};
  rules[R2_EXP] = {{OP_SMALLER, A_EXP, R2_EXP},
                   {OP_SMALLER_OR_EQ, A_EXP, R2_EXP},
                   {OP_GREATER, A_EXP, R2_EXP},
                   {OP_GREATER_OR_EQ, A_EXP, R2_EXP},
                   {OP_EQUAL, A_EXP, R2_EXP},
                   {OP_NOT_EQUAL, A_EXP, R2_EXP},
                   {EMPTY}};
  rules[A_EXP] = {{AU_EXP, A2_EXP}};
  rules[A2_EXP] = {{OP_ADD, AU_EXP, A2_EXP}, {OP_SUB, AU_EXP, A2_EXP}, {EMPTY}};
  rules[AU_EXP] = {{POW_EXP, AU2_EXP}};
  rules[AU2_EXP] = {
      {OP_MULT, POW_EXP, AU2_EXP}, {OP_DIV, POW_EXP, AU2_EXP}, {EMPTY}};
  rules[POW_EXP] = {{FIM_EXP, POW_EXP2}};
  rules[POW_EXP2] = {{OP_EXP, POW_EXP}, {EMPTY}};
  rules[FIM_EXP] = {{}}; // TODO
  rules[REF_VAR] = {{KW_REF, OPEN_PAREN, VAR, CLOSE_PAREN}};
  rules[DEREF_VAR] = {{KW_DEREF, OPEN_PAREN, VAR, CLOSE_PAREN}};
  rules[REC_VAR] = {{OPEN_PAREN, REC_VAR, CLOSE_PAREN},
                    {DEREF_VAR, KW_DOT, ID},
                    {CALL_STMT, KW_DOT, ID}};
  rules[VAR] = {
      {OPEN_PAREN, REC_VAR, CLOSE_PAREN}, {NAMELESS_VAR}, {ID, NAME_VAR}};
  rules[NAME_VAR] = {{EMPTY}, {NAME_CALL_STMT, KW_DOT, ID}};
  rules[NAMELESS_VAR] = {{DEREF_VAR, KW_DOT, ID}};
  rules[NAMELESS_DEREF_VAR_VAR] = {{KW_DOT, ID}};
  rules[NO_PAREN_VAR] = {{NAMELESS_VAR}, {ID, NAME_VAR}};
  rules[LITERAL] = {{FLOAT_LITERAL},
                    {INT_LITERAL},
                    {STRING_LITERAL},
                    {BOOL_LITERAL},
                    {KW_NULL}};
  rules[BOOL_LITERAL] = {{KW_FALSE}, {KW_TRUE}};
  rules[STMT] = {{IF_STMT},       {WHILE_STMT},
                 {RETURN_STMT},   {NAMELESS_ASSIGN_STMT},
                 {ID, NAME_STMT}, {DO_STMT}};
  rules[NAME_STMT] = {{OP_ASSIGN, EXP},
                      {NAME_CALL_STMT, OPT_DOT_NAME_ASSIGN_EXP}};
  rules[OPT_DOT_NAME_ASSIGN_EXP] = {{KW_DOT, ID, OP_ASSIGN, EXP}, {EMPTY}};
  rules[ASSIGN_STMT] = {{ID, NAME_ASSIGN_STMT}, {NAMELESS_ASSIGN_STMT}};
  rules[NAME_ASSIGN_STMT] = {{NAME_VAR, OP_ASSIGN, EXP}};
  rules[NAMELESS_ASSIGN_STMT] = {{DEREF_VAR, OPT_DOT_NAME, OP_ASSIGN, EXP}};
  rules[OPT_DOT_NAME] = {{EMPTY}, {KW_DOT, ID}};
  rules[IF_STMT] = {{KW_IF, EXP, KW_THEN, STMT_LIST, T_IF_STMT, KW_FI}};
  rules[T_IF_STMT] = {{KW_ELSE, STMT_LIST}, {EMPTY}};
  rules[WHILE_STMT] = {{KW_WHILE, EXP, KW_DO, STMT_LIST, KW_OD}};
  rules[RETURN_STMT] = {{KW_RETURN, EXP}};
  rules[CALL_STMT] = {{ID, NAME_CALL_STMT}};
  rules[NAME_CALL_STMT] = {{OPEN_PAREN, T_CALL_STMT, CLOSE_PAREN}};
  rules[T_CALL_STMT] = {{EXP, U_CALL_STMT}, {EMPTY}};
  rules[U_CALL_STMT] = {{KW_COMMA, EXP, U_CALL_STMT}, {EMPTY}};
  rules[DO_STMT] = {{KW_DO, DO_STMT_LIST, KW_OD}};
  rules[DO_STMT_LIST] = {
      {KW_EXIT, KW_WHEN, EXP}, {IF_STMT}, {RETURN_STMT}, {NAMELESS_ASSIGN_STMT},
      {ID, NAME_STMT},         {DO_STMT}, {EMPTY}};
  rules[TYPE] = {{KW_FLOAT}, {KW_INT}, {KW_STRING},
                 {KW_BOOL},  {ID},     {KW_REF, OPEN_PAREN, TYPE, CLOSE_PAREN}};
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
