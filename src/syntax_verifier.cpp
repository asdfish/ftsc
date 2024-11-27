#include <syntax_verifier.hpp>

#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>

static int walk_callback(const TSNode& node, void* user_data);

static int walk_callback(const TSNode& node, void* user_data) {
  if(strcmp(ts_node_type(node), "ERROR") != 0)
    return 0;

  SyntaxVerifier* syntax_verifier = (SyntaxVerifier*) user_data;
  size_t start_byte = ts_node_start_byte(node);
  size_t end_byte = ts_node_end_byte(node);
  std::cerr << "line " << syntax_verifier->source_code.line_number(start_byte) << ":\n" <<
    syntax_verifier->source_code.contents.substr(start_byte, end_byte) << '\n';
  return -1;
}

SyntaxVerifier::SyntaxVerifier(Arguments* arguments, TreeSitter* tree_sitter) {
  this->arguments = arguments;
  this->tree_sitter = tree_sitter;
}
std::string SyntaxVerifier::verify(void) {
  std::stringstream file_contents_buffer;

  for(const std::string& file_path : arguments->input_files) {
    std::ifstream file = std::ifstream(file_path, std::ios::in);
    if(!file.good())
      return "Failed to open file \'" + file_path + "\'\n";

    file_contents_buffer << file.rdbuf() << '\n';

    file.close();
  }

  source_code.set_contents(file_contents_buffer.str());
  tree_sitter->parse(source_code.contents);

  int result = tree_sitter->walk(walk_callback, this);
  if(result)
    return "Syntax error";
  return "";
}
