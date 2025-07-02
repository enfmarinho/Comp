#include "type.hpp"
#include "base_type.hpp"
#include "symbol_table.hpp"

Type::Type(BaseType base_type) : base_type(base_type) {}

Type::Type(BaseType base_type, Type *referenced_type)
    : base_type(base_type), referenced_type(referenced_type) {}

Type::Type(BaseType base_type, std::vector<Type *> param_types,
           Type *return_type)
    : base_type(base_type), param_types(param_types),
      return_type(return_type){};

Type::Type(BaseType base_type, std::string struct_type_name)
    : base_type(base_type), struct_type_name(struct_type_name) {}

Type::Type(BaseType base_type, std::string struct_type_name,
           SymbolTable *symbol_table_cp)
    : base_type(base_type), struct_type_name(struct_type_name) {
  symbol_table = new SymbolTable();
  *symbol_table = *symbol_table_cp;
}
