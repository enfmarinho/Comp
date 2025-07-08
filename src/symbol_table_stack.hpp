#ifndef SYMBOL_TABLE_STACK_HPP
#define SYMBOL_TABLE_STACK_HPP

#include "symbol_table.hpp"
#include <string>
#include <vector>

class SymbolTableStack {
public:
  SymbolTableStack() { open_scope(); };
  ~SymbolTableStack() = default;

  void open_scope() { m_symbol_table_stack.push_back(SymbolTable()); }

  void close_scope() { m_symbol_table_stack.pop_back(); }

  void insert(std::pair<std::string, Symbol> value) {
    m_symbol_table_stack.back().insert(value);
  }

  SymbolTable top() { return m_symbol_table_stack.back(); }

  bool consult(std::string id, Symbol &symbol) {
    for (auto it = m_symbol_table_stack.rbegin();
         it != m_symbol_table_stack.rend(); ++it) {
      if (it->consult(id, symbol))
        return true;
    }
    return false;
  }

private:
  std::vector<SymbolTable> m_symbol_table_stack;
};

#endif // !SYMBOL_TABLE_STACK_HPP
