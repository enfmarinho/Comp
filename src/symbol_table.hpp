#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "type.hpp"
#include <cassert>
#include <string>
#include <unordered_map>

struct Symbol {
  std::string internal_name;
  Type type;

  Symbol() = default;
  Symbol(std::string internal_name, Type type)
      : internal_name(internal_name), type(type) {}
};

class SymbolTable {
public:
  SymbolTable() = default;

  /// Inserts "element" into the symbol table
  void insert(const std::pair<std::string, Symbol> element);

  /// Returns the last inserted element that matches "id"
  bool consult(const std::string &id, Symbol &result);

  /// Removes the last inserted element that matches "id"
  void remove(const std::string &id);

private:
  std::unordered_multimap<std::string, Symbol> symbol_table;
};

#endif // !SYMBOL_TABLE_HPP
