#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "type.hpp"
#include <cassert>
#include <string>
#include <unordered_map>

class SymbolTable {
public:
  SymbolTable() = default;

  /// Inserts "element" into the symbol table
  void insert(const std::pair<std::string, Type> element);

  /// Returns the last inserted element that matches "id"
  bool consult(const std::string &id, Type &result);

  /// Removes the last inserted element that matches "id"
  void remove(const std::string &id);

  std::vector<std::pair<std::string, Type>> get_entries();

private:
  std::unordered_multimap<std::string, Type> symbol_table;
};

#endif // !SYMBOL_TABLE_HPP
