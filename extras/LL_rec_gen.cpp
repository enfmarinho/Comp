#include <cassert>
#include <cctype>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#define INPUT_FILE "left_recursive_table.txt"
#define OUTPUT_FILE "LL_rec.cpp"
#define SymbolType int

std::unordered_map<std::string,
                   std::unordered_map<std::string, std::vector<std::string>>>
    table;

void read_file(std::ifstream &file_in);
void write_includes(std::ofstream &file_out);
void write_general_defs(std::ofstream &file_out);
void write_func_signatures(std::ofstream &file_out);
void write_main(std::ofstream &file_out);
void write_func_defs(std::ofstream &file_out);

int main(int argc, char *argv[]) {
  std::ifstream file_in(INPUT_FILE);
  if (!file_in) {
    std::cerr << "Could not open input file" << std::endl;
    return 1;
  }
  read_file(file_in);
  file_in.close();

  std::ofstream file_out(OUTPUT_FILE);
  if (!file_out) {
    std::cerr << "Could not open output file" << std::endl;
    return 1;
  }
  write_includes(file_out);
  write_general_defs(file_out);
  write_func_signatures(file_out);
  write_main(file_out);
  write_func_defs(file_out);
  file_out.close();

  return 0;
}

void read_file(std::ifstream &file_in) {
  std::string line, token;
  std::getline(file_in, line);
  std::stringstream iss(line);

  std::vector<std::string> terminal_symbols;
  std::getline(iss, line, ','); // Discard first value
  while (std::getline(iss, token, ',')) {
    assert(!token.empty());
    terminal_symbols.push_back(token);
  }

  while (!file_in.eof()) {
    std::getline(file_in, line);
    iss.str(line);
    std::string non_terminal_symbol, table_value;
    std::getline(iss, non_terminal_symbol, ',');

    auto line_it = table.find(non_terminal_symbol);
    for (int i = 0; i < terminal_symbols.size(); ++i) {

      std::getline(iss, table_value, ',');
      if (table_value.empty())
        continue;

      auto column_it = line_it->second.find(terminal_symbols[i]);
      std::istringstream iss2(table_value);
      iss2 >> token;
      assert(token == non_terminal_symbol);
      iss2 >> token;
      assert(token == "::=");

      while (iss2 >> token) {
        if (token == "ε") // TODO is it possible to do that ?
          token = "empty";

        column_it->second.push_back(token);
      }
    }
  }
}

void write_includes(std::ofstream &file_out) {
  file_out << "#include \"../build/lex.yy.cc\"\n";
  file_out << "#include \"../build/parser.tab.hpp\"\n";
  file_out << "#include <unordered_map>\n";
  file_out << "#include <iostream>\n";
  file_out << "#include <cstdlib>\n";
}

void write_general_defs(std::ofstream &file_out) {
  file_out << "#define SymbolType int" << "\n";
  file_out << "SymbolType token = yylex();" << "\n";
  file_out << "YYSTYPE yylval;" << "\n";

  file_out << "void error() {\n"
           << "int line, column;\n"
           << "if (token == INT_LITERAL) {\n"
           << "line = yylval.int_value.line; \n"
           << "column = yylval.int_value.column;\n"
           << "} else if (token == FLOAT_LITERAL) {\n"
           << "line = yylval.float_value.line;\n"
           << "column = yylval.float_value.column;\n"
           << "}\n"
           << "else if (token == STRING_LITERAL) {\n"
           << "line = yylval.string_value.line;\n"
           << "column = yylval.string_value.column;\n"
           << "}\n"
           << "else if (token == ID) {\n"
              "line = yylval.id.line;\n"
           << "column = yylval.id.column;\n"
           << "}\n"
           << "else {\n"
           << "line = yylval.general_values.line;\n"
           << "column = yylval.general_values.column;\n"
           << "}\n"
           << "std::cout << \"Error at line \" << line << \" and at column \" "
           << "<< column;\n"
           << "exit(1);\n"
           << "}\n";

  file_out << "void process_input(SymbolType expected_token){\n"
           << "if (token != expected_token)\n"
           << "error();\n"
           << "else\n"
           << "token = yylex();\n"
           << "}\n";
}

void write_func_signatures(std::ofstream &file_out) {
  for (auto entry : table) {
    file_out << "void f_" << entry.first << "();\n";
  }
}

void write_main(std::ofstream &file_out) {
  file_out << "int main() {" << "\n";
  file_out << "    f_PROGRAM();" << "\n";
  file_out << "}" << "\n";
}

bool is_terminal(std::string symbol) {
  assert(!symbol.empty());
  // If symbol is written in lower case is a terminal symbol
  return symbol[0] > 'Z';
}

std::string to_upper(std::string s) {
  std::string ans;
  ans.reserve(s.size());
  for (const char &c : s) {
    assert(islower(c));
    ans.push_back(std::toupper(c));
  }

  return ans;
}

void write_func_defs(std::ofstream &file_out) {
  for (auto line : table) {
    file_out << "void f_" << line.first << "(){\n";

    file_out << "switch(token){\n";
    for (auto column : line.second) {
      file_out << "case " << column.first << ":\n";
      for (auto symbol : column.second) {
        if (symbol == "EMPTY") {

        } else if (is_terminal(symbol))
          file_out << "process_input(" << to_upper(symbol) << ");\n";
        else
          file_out << "f_" << symbol << "();\n";
      }
      file_out << "break;\n";
    }
    file_out << "default: error();\n";
    file_out << "}\n";

    file_out << "}\n";
  }
}
