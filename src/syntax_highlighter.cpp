#include <source_code.hpp>
#include <syntax_highlighter.hpp>

extern "C" {
#include <tree_sitter/api.h>
}

SyntaxHighlighter::SyntaxHighlighter(const std::string& source_code) {
  set_source_code(source_code);
}
SyntaxHighlighter::SyntaxHighlighter(const std::string& source_code, const TSNode& node) {
  set_source_code(source_code.substr(ts_node_start_byte(node), ts_node_end_byte(node)));
}
SyntaxHighlighter::SyntaxHighlighter(const SourceCode& source_code) {
  set_source_code(source_code.contents);
}
std::string SyntaxHighlighter::highlight(void) const {
  return "";
}
void SyntaxHighlighter::set_source_code(const std::string& source_code) {
  this->source_code = source_code;
  tree_sitter.parse(source_code);
}
