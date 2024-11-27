#include <tree_sitter.hpp>
#include <tree-sitter-typescript.h>

#include <vector>

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
void TreeSitter::parse(const SourceCode& source_code) {
  parse(source_code.contents);
}
void TreeSitter::parse(const std::string& string) {
  tree = ts_parser_parse_string(parser, tree, string.c_str(), string.length());
}
int TreeSitter::walk(std::function<int(const TSNode& node, void* user_data)> callback, void* user_data) {
  if(!tree)
    return 0;

  std::vector<TSNode> to_walk { ts_tree_root_node(tree) };

  while(!to_walk.empty()) {
    const TSNode& node = to_walk.back();
    to_walk.pop_back();

    int result = callback(node, user_data);
    if(result)
      return result;

    for(size_t i = 0; i < ts_node_named_child_count(node); i ++)
      to_walk.push_back(ts_node_named_child(node, i));
  }

  return 0;
}
