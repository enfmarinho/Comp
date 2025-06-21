#ifndef TYPE_HPP
#define TYPE_HPP

#include "base_type.hpp"
#include <memory>
#include <string>
#include <vector>

class SymbolTable;

struct Type {
  BaseType base_type;
  std::shared_ptr<Type>
      referenced_type; // For Reference type, nullptr otherwise
  std::vector<std::shared_ptr<Type>>
      param_types;                     // For procedure type, empty otherwise
  std::shared_ptr<Type> return_type;   // For procedure type, nullptr otherwise
  std::string struct_type_name;        // For struct variables
  SymbolTable *symbol_table = nullptr; // For struct declarations

  Type(BaseType base_type);

  Type(BaseType base_type, std::shared_ptr<Type> referenced_type);

  Type(BaseType base_type, std::vector<std::shared_ptr<Type>> parem_types,
       std::shared_ptr<Type> return_type);

  Type(BaseType base_type, std::string struct_type_name);

  Type(BaseType base_type, std::string struct_type_name,
       SymbolTable *symbol_table_cp);

  Type(const Type &) = default;
  Type &operator=(const Type &) = default;
  ~Type() = default;
};

#endif // #ifndef TYPE_HPP
