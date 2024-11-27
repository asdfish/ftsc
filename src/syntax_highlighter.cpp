#include <source_code.hpp>
#include <syntax_highlighter.hpp>
#include <utils.hpp>

#include <algorithm>
#include <iostream>

extern "C" {
#include <tree_sitter/api.h>
}

SyntaxHighlighter::SyntaxHighlighter(Arguments* arguments_p, const std::string& source_code) {
  this->arguments_p = arguments_p;
  set_source_code(source_code);
}
SyntaxHighlighter::SyntaxHighlighter(Arguments* arguments_p, const std::string& source_code, const TSNode& node) {
  this->arguments_p = arguments_p;
  set_source_code(source_code.substr(ts_node_start_byte(node), ts_node_end_byte(node)));
}
SyntaxHighlighter::SyntaxHighlighter(Arguments* arguments_p, const SourceCode& source_code) {
  this->arguments_p = arguments_p;
  set_source_code(source_code.contents);
}
std::string SyntaxHighlighter::highlight(void) {
  nodes.clear();
  tree_sitter.walk(walk_callback, (void*) this);
  if(!nodes.size())
    return "";

  std::vector<size_t> breakpoints;
  breakpoints.reserve((nodes.size() * 2) + 2);
  breakpoints.push_back(0);
  for(const TSNode& node : nodes) {
    breakpoints.push_back(ts_node_start_byte(node));
    breakpoints.push_back(ts_node_end_byte(node));
  }
  breakpoints.push_back(source_code.length());

  std::sort(breakpoints.begin(), breakpoints.end());

  std::vector<std::string> splits;
  splits.reserve(breakpoints.size() / 2);
  for(size_t i = 0; i < breakpoints.size() - 1; i ++) {
    size_t min = breakpoints[i];
    size_t max = breakpoints[i + 1];

    splits.push_back(source_code.substr(min, max - min));
  }

  for(const std::string& split : splits)
    std::cout << split << '\n';
  return "";
}
void SyntaxHighlighter::set_source_code(const std::string& source_code) {
  this->source_code = source_code;
  tree_sitter.parse(source_code);
}

int SyntaxHighlighter::walk_callback(const TSNode& node, void* user_data) {
  SyntaxHighlighter* syntax_highlighter = (SyntaxHighlighter*) user_data;

  std::string answer = safe_map_at<std::string, std::string>(syntax_highlighter->arguments_p->node_colors, std::string(ts_node_type(node)));
  if(!answer.length())
    return 0;

  syntax_highlighter->nodes.push_back(node);
  return 0;
}
