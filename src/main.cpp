#include "parser.tab.hpp"
#include <string>

extern int yyparse();

std::string path_file_out;

int main(int argc, char *argv[]) {
  if (argc > 1)
    path_file_out = argv[1];
  else
    path_file_out = "three_address_code.c";

  yyparse();
  return 0;
}
