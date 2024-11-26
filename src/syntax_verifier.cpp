#include <syntax_verifier.hpp>

#include <sstream>
#include <fstream>

SyntaxVerifier::SyntaxVerifier(Arguments* arguments, TreeSitter* tree_sitter) {
  this->arguments = arguments;
  this->tree_sitter = tree_sitter;
}

std::string SyntaxVerifier::verify(void) {
  std::string file_contents_concat = "";
  for(const std::string& file_path : arguments->input_files) {
    std::ifstream file = std::ifstream(file_path);
    if(!file.good())
      return "Failed to open file " + file_path;

    std::stringstream string_buffer;
    string_buffer << file.rdbuf();
    file_contents_concat += string_buffer.str() + "\n";

    file.close();
  }

  tree_sitter->parse(file_contents_concat);
  return "";
}
