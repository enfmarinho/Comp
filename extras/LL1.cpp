#include <cassert>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

#include "../build/lex.yy.cc"
#include "../build/parser.tab.hpp"
#include "non_terminals.h"

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
void print_usage();

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
