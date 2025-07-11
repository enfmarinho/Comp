#ifndef TYPE_HPP
#define TYPE_HPP

#include "base_type.hpp"
#include <string>
#include <vector>

class SymbolTable;
class Data;

struct Type {
  BaseType base_type;
  Type *referenced_type{nullptr};     // For Reference type, nullptr otherwise
  std::vector<Data *> param_types;    // For procedure type, empty otherwise
  Type *return_type{nullptr};         // For procedure type, nullptr otherwise
  std::string return_var_name;        // For procedure type, empty otherwise
  std::string struct_type_name;       // For struct variables
  SymbolTable *symbol_table{nullptr}; // For struct declarations

  Type(BaseType base_type);

  Type(BaseType base_type, Type *referenced_type);

  Type(BaseType base_type, std::vector<Data *> param_types, Type *return_type,
       std::string return_var_name);

  Type(BaseType base_type, std::string struct_type_name);

  Type(BaseType base_type, std::string struct_type_name,
       SymbolTable *symbol_table_cp);

  Type() = default;
  Type(const Type &) = default;
  Type &operator=(const Type &) = default;
  Type &operator=(Type &) = default;
  ~Type() = default;
};

#endif // #ifndef TYPE_HPP
