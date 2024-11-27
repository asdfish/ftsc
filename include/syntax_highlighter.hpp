#ifndef SYNTAX_HIGHLIGHTER_HPP
#define SYNTAX_HIGHLIGHTER_HPP

#include <arguments.hpp>
#include <tree_sitter.hpp>

extern "C" {
#include <tree_sitter/api.h>
}

class SourceCode;

#include <string>
#include <vector>

class SyntaxHighlighter {
  public:
    const Arguments* arguments_p = NULL;
    std::string source_code;
    TreeSitter tree_sitter;

    SyntaxHighlighter(const Arguments* arguments_p, const std::string& source_code);
    SyntaxHighlighter(const Arguments* arguments_p, const std::string& source_code, const TSNode& node);
    SyntaxHighlighter(const Arguments* arguments_p, const SourceCode& source_code);
    std::string highlight(void);
    void set_source_code(const std::string& source_code);
  private:
    std::vector<TSNode> nodes;

    static int walk_callback(const TSNode& node, void* user_data);
};

#endif
