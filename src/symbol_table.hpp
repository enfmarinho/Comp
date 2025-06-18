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

  std::vector<Type> get_types() {
    std::vector<Type> types;
    for (auto it = symbol_table.begin(); it != symbol_table.end(); ++it) {
      types.push_back(it->second);
    }
    return types;
  }

private:
  std::unordered_multimap<std::string, Type> symbol_table;
};

#endif // !SYMBOL_TABLE_HPP
