#include "parser.tab.hpp"
#include <fstream>

extern int yyparse();

std::ofstream file_out;

int main(int argc, char *argv[]) {
  if (argc > 1)
    file_out = std::ofstream(argv[1]);
  else
    file_out = std::ofstream("three_address_code.c");

  yyparse();
  file_out.close();
  return 0;
}
