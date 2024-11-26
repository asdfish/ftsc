#include <syntax_verifier.hpp>

SyntaxVerifier::SyntaxVerifier(Arguments* arguments, TreeSitter* tree_sitter) {
  this->arguments = arguments;
  this->tree_sitter = tree_sitter;
}

std::string SyntaxVerifier::verify(void) {
  return "";
}
