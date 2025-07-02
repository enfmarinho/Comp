#include "parser.tab.hpp"
#include <ifstream>

extern int yyparse();

std::ifstream file_out;

int main(int argc, char *argv[]) {
  if (argc > 1)
    file_out = std::ifstream(argv[1]);
  else
    file_out = std::ifstream("three_address_code.c");

  yyparse();
  file_out.close();
  return 0;
}
