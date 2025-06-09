#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "parser.tab.hpp"
#include <cassert>
#include <string>
#include <unordered_map>

struct Symbol {
  yytokentype token;
  std::string type;
};

class SymbolTable {
public:
  /// Inserts "element" into the symbol table
  void insert(const std::pair<std::string, Symbol> element);

  /// Returns the last inserted element that matches "key"
  Symbol consult(const std::string &key);

  /// Removes the last inserted element that matches "key"
  void remove(const std::string &key);

private:
  std::unordered_multimap<std::string, Symbol> symbol_table;
};

#endif // !SYMBOL_TABLE_HPP
