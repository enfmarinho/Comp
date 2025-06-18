#ifndef TYPE_H
#define TYPE_H

#include "../build/parser.tab.hpp"
#include <memory>
#include <string>
#include <vector>
class SymbolTable;

// enum BaseType {
//   VOID,
//   INT,
//   FLOAT,
//   STRING,
//   BOOL,
//   PROCEDURE,
//   STRUCT,
//   REFERENCE,
//   ERROR,
// };

struct Type {
  yytokentype base_type;
  std::shared_ptr<Type>
      referenced_type; // For Reference type, nullptr otherwise
  std::vector<std::shared_ptr<Type>>
      param_types;                     // For procedure type, empty otherwise
  std::shared_ptr<Type> return_type;   // For procedure type, nullptr otherwise
  std::string struct_name;             // For struct types, empty otherwise
  SymbolTable *symbol_table = nullptr; // For struct types
};

#endif // #ifndef TYPE_H
