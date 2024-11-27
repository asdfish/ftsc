#include <syntax_verifier.hpp>

#include <cstring>
#include <iostream>
#include <sstream>

static int walk_callback(const TSNode& node, void* user_data) {
  if(strcmp(ts_node_type(node), "ERROR") != 0)
    return 0;

  SourceCode* source_code = (SourceCode*) user_data;

  size_t start_byte = ts_node_start_byte(node);
  size_t end_byte = ts_node_end_byte(node);
  std::cerr << "line " << source_code->line_number(start_byte) + 1 << " - " << source_code->line_number(end_byte) + 1 << ":\n" <<
    source_code->contents.substr(start_byte, end_byte) << '\n';
  return -1;
}

SyntaxVerifier::SyntaxVerifier(void) {}
std::string SyntaxVerifier::verify(const SourceCode& source_code, TreeSitter& tree_sitter) {
  int result = tree_sitter.walk(walk_callback, (void*) &source_code);
  if(result)
    return "Syntax error";
  return "";
}
