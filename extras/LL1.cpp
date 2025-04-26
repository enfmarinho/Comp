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
  else if (symbol == "T_PROGRAM")
    return T_PROGRAM;
  else if (symbol == "U_PROGRAM")
    return U_PROGRAM;
  else if (symbol == "DECL")
    return DECL;
  else if (symbol == "VAR_DECL")
    return VAR_DECL;
  else if (symbol == "T_VAR_DECL")
    return T_VAR_DECL;
  else if (symbol == "U_VAR_DECL")
    return U_VAR_DECL;
  else if (symbol == "PROC_DECL")
    return PROC_DECL;
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
  else if (symbol == "REC_DECL")
    return REC_DECL;
  else if (symbol ==) // TODO write those the missing symbols
    return;
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
