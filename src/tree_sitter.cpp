#include <tree_sitter.hpp>
#include <tree-sitter-typescript.h>

TreeSitter::TreeSitter(void) {
  parser = ts_parser_new();
  ts_parser_set_language(parser, tree_sitter_typescript());
}

TreeSitter::~TreeSitter(void) {
  if(parser)
    ts_parser_delete(parser);
  if(tree)
    ts_tree_delete(tree);
}

void TreeSitter::parse(const std::string& string) {
  tree = ts_parser_parse_string(parser, tree, string.c_str(), string.length());
}
