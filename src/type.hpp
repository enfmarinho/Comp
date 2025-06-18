#ifndef TYPE_H
#define TYPE_H

#include "../build/parser.tab.hpp"
#include <memory>
#include <string>
#include <vector>

class SymbolTable;

struct Type {
  yytokentype base_type;
  std::shared_ptr<Type>
      referenced_type; // For Reference type, nullptr otherwise
  std::vector<std::shared_ptr<Type>>
      param_types;                     // For procedure type, empty otherwise
  std::shared_ptr<Type> return_type;   // For procedure type, nullptr otherwise
  std::string struct_type_name;        // For struct types, empty otherwise
  SymbolTable *symbol_table = nullptr; // For struct types

  Type(yytokentype base_type);

  Type(yytokentype base_type, std::shared_ptr<Type> referenced_type);

  Type(yytokentype base_type, std::vector<std::shared_ptr<Type>> parem_types,
       std::shared_ptr<Type> return_type);

  Type(yytokentype base_type, std::string struct_type_name,
       SymbolTable *symbol_table_cp);
};

#endif // #ifndef TYPE_H
