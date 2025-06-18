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
  int bucket = symbol_table.bucket(id);
  for (auto it = symbol_table.cbegin(bucket); it != symbol_table.cend(bucket);
       ++it) {
    if (it->first == id)
      last_inserted = it;
  }
  assert(last_inserted != symbol_table.cend(bucket));
  result = last_inserted->second;
  return true;
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
