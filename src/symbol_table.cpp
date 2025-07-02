#include "symbol_table.hpp"

#include <cassert>
#include <string>
#include <unordered_map>

/// Inserts "element" into the symbol table
void SymbolTable::insert(const std::pair<std::string, Type> element) {
  symbol_table.insert(element);
}

/// Returns the last inserted element that matches "id"
bool SymbolTable::consult(const std::string &id, Type &result) {
  bool found = false;
  int bucket = symbol_table.bucket(id);
  for (auto it = symbol_table.cbegin(bucket); it != symbol_table.cend(bucket);
       ++it) {
    if (it->first == id) {
      result = it->second;
      found = true;
    }
  }
  return found;
}

/// Removes the last inserted element that matches "id"
void SymbolTable::remove(const std::string &id) {
  // Unfortunately there is no better way
  auto range = symbol_table.equal_range(id);
  if (range.first != range.second) { // Ensure key exists
    auto last = range.first;
    for (auto it = range.first; it != range.second; ++it) {
      last = it; // store the last occurrence of key, i.e. last inserted value
                 // that matches "key"
    }
    symbol_table.erase(last);
  }
}

std::vector<std::pair<std::string, Type>> SymbolTable::get_entries() {
  std::vector<std::pair<std::string, Type>> entries;
  for (auto entry : symbol_table)
    entries.push_back(entry);

  return entries;
}
