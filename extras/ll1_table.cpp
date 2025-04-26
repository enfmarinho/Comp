#include <cassert>
#include <iostream>
#include <stack>
#include <vector>

#include "../build/lex.yy.cc"
#include "../build/parser.tab.hpp"
#include "non_terminals.h"

#define NUMBER_OF_TERMINALS 55
#define SymbolType int

// Global variables
YYSTYPE yylval;
std::vector<SymbolType> Table[NUMBER_OF_NON_TERMINALS][NUMBER_OF_TERMINALS];

// Functions signatures
bool LL(std::stack<SymbolType> &stack);
std::vector<SymbolType> &consult_table(SymbolType non_terminal,
                                       SymbolType terminal);
bool is_terminal(SymbolType symbol);
void error();
void initialize_table();

int main(int argc, char *argv[]) {
  initialize_table();

  std::stack<SymbolType> stack;
  stack.push(END);
  stack.push(PROGRAM);

  bool reached_input_end = LL(stack);

  if (stack.empty() && reached_input_end) {
    std::cout << "Input belongs to grammar" << std::endl;
  } else {
    std::cout << "Input doesn't belong to grammar" << std::endl;
  }

  return 0;
}

bool LL(std::stack<SymbolType> &stack) {
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
  return Table[non_terminal][terminal];
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

void initialize_table() {
  // TODO
}
