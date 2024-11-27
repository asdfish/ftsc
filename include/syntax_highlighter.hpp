#ifndef SYNTAX_HIGHLIGHTER_HPP
#define SYNTAX_HIGHLIGHTER_HPP

#include <tree_sitter.hpp>

class SourceCode;
struct TSNode;

#include <string>

class SyntaxHighlighter {
  public:
    std::string source_code;
    TreeSitter tree_sitter;

    SyntaxHighlighter(const std::string& source_code);
    SyntaxHighlighter(const std::string& source_code, const TSNode& node);
    SyntaxHighlighter(const SourceCode& source_code);
    std::string highlight(void) const;

    void set_source_code(const std::string& source_code);
};

#endif
