#include "simble_table.hpp"

#include <cassert>
#include <string>
#include <unordered_map>

/// Inserts "element" into the symbol table
void SymbolTable::insert(const std::pair<std::string, Symbol> element) {
  symbol_table.insert(element);
}

/// Returns the last inserted element that matches "id"
Symbol SymbolTable::consult(const std::string &id) {
  int bucket = symbol_table.bucket(id);
  auto last_inserted = symbol_table.cbegin(bucket);
  for (auto it = symbol_table.cbegin(bucket); it != symbol_table.cend(bucket);
       ++it) {
    if (it->first == id)
      last_inserted = it;
  }
  assert(last_inserted != symbol_table.cend(bucket));
  return last_inserted->second;
}

/// Removes the last inserted element that matches "id"
void SymbolTable::remove(const std::string &id) {
  // Unfortunately there is no better waid
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

