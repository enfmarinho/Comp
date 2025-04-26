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

// 1d for the symbols, 2d for each rule of the symbol, 3d for each symbol of the
// rule
std::vector<std::vector<SymbolType>>
    rules[NUMBER_OF_TERMINALS + NUMBER_OF_NON_TERMINALS];

// Functions signatures
bool LL_table(std::stack<SymbolType> &stack);
std::vector<SymbolType> &consult_table(SymbolType non_terminal,
                                       SymbolType terminal);
void init_table();

bool LL_rec(std::stack<SymbolType> &stack);
std::vector<std::vector<SymbolType>> &consult_rules(SymbolType symbol);
void init_rules();

bool is_terminal(SymbolType symbol);
void error();
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

  bool reached_input_end;
  if (std::strcmp(argv[1], "-table") == 0) {
    init_table();
    reached_input_end = LL_table(stack);
  } else if (std::strcmp(argv[1], "-rec") == 0) {
    init_rules();
    reached_input_end = LL_rec(stack);
  } else {
    print_usage();
    return 1;
  }

  if (stack.empty() && reached_input_end) {
    std::cout << "Input belongs to grammar" << std::endl;
  } else {
    std::cout << "Input doesn't belong to grammar" << std::endl;
  }

  return 0;
}

bool LL_table(std::stack<SymbolType> &stack) {
  SymbolType input_symbol;
  bool symbol_read = false;
  bool reached_input_end = false;

  while (!stack.empty() && !reached_input_end) {
    SymbolType top_stack_symbol = stack.top();
    if (!symbol_read) {
      SymbolType symbol = yylex();
      symbol_read = true;
      if (symbol == 0) {
        symbol = END;
        reached_input_end = true;
      }
    }

    if (is_terminal(top_stack_symbol)) {
      if (top_stack_symbol == input_symbol) {
        stack.pop();
        symbol_read = false;
      } else {
        error();
        break;
      }
    } else if (!consult_table(top_stack_symbol, input_symbol)
                    .empty()) { // If there is a relevant rule associated to the
                                // non-terminal symbol at the top of the stack
      stack.pop();
      for (SymbolType t : consult_table(top_stack_symbol, input_symbol)) {
        if (t != EMPTY) { // Add symbols in table to the stack, except when
                          // symbol is empty
          stack.push(t);
        }
      }
    } else {
      error();
      break;
    }
  }

  return reached_input_end;
}

std::vector<SymbolType> &consult_table(SymbolType non_terminal,
                                       SymbolType terminal) {
  terminal = terminal - EMPTY;
  assert(non_terminal >= 0 && non_terminal <= NUMBER_OF_NON_TERMINALS &&
         "Try to index Table with an out of bound index");
  assert(terminal >= 0 && terminal <= NUMBER_OF_TERMINALS &&
         "Try to index Table with an out of bound index");
  return table[non_terminal][terminal];
}

void init_table() {
  // TODO
}

bool LL_rec(std::stack<SymbolType> &stack, SymbolType &curr_symbol,
            bool &reached_input_end) {

  if (reached_input_end) {
    return false;
  }

  if (curr_symbol == 0 && !reached_input_end) {
    curr_symbol = yylex();
    if (curr_symbol == 0) {
      curr_symbol = END;
      reached_input_end = true;
    }
  }
  SymbolType top_stack_symbol = stack.top();
  if (is_terminal(top_stack_symbol)) {
    if (top_stack_symbol == curr_symbol) {
      curr_symbol = 0;
      stack.pop();
      return true;
    } else {
      return false;
    }
  }

  for (const std::vector<SymbolType> &rule : consult_rules(top_stack_symbol)) {
    // Try each of those rules hopping for a match
    std::stack<SymbolType> stack_cp = stack;
    stack.pop();
    for (SymbolType s : rule) {
      stack.push(s);
    }
    if (LL_rec(stack_cp, curr_symbol, reached_input_end)) {
      return true;
    }
  }

  return false;
}

std::vector<std::vector<SymbolType>> &consult_rules(SymbolType symbol) {
  if (symbol >= EMPTY) {
    symbol = symbol - EMPTY + NUMBER_OF_NON_TERMINALS;
    assert(symbol >= NUMBER_OF_NON_TERMINALS &&
           symbol < NUMBER_OF_NON_TERMINALS + NUMBER_OF_TERMINALS);
  }
  return rules[symbol];
}

void init_rules() {
  // TODO
}

bool is_terminal(SymbolType symbol) { return symbol >= EMPTY; }

void error(SymbolType symbol) {
  int line, column;
  if (symbol == INT_LITERAL) {
    line = yylval.int_value.line;
    column = yylval.int_value.column;
  } else if (symbol == FLOAT_LITERAL) {
    line = yylval.float_value.line;
    column = yylval.float_value.column;
  } else if (symbol == STRING_LITERAL) {
    line = yylval.string_value.line;
    column = yylval.string_value.column;
  } else if (symbol == ID) {
    line = yylval.id.line;
    column = yylval.id.column;
  } else {
    line = yylval.general_values.line;
    column = yylval.general_values.column;
  }
  std::cout << "Error at line " << line << "and at column " << column
            << std::endl;
}

void print_usage() {
  std::cout << "Missing or invalid commend line argument! Must be -table or "
               "-rec, representing the LL algorithm to be used"
            << std::endl;
}
