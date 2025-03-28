#include "parser.tab.hpp"
#include <iostream>

extern int yyparse();

int main(int argc, char *argv[]) {
  std::cout << "parsing... " << std::endl;
  yyparse();
  std::cout << "done" << std::endl;
  return 0;
}
