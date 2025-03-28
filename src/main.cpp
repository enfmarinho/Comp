#include "parser.tab.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "parsing... " << std::endl;
  yyparse();
  std::cout << "done" << std::endl;
  return 0;
}
