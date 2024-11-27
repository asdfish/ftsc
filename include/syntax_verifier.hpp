#ifndef SYNTAX_VERIFIER_HPP
#define SYNTAX_VERIFIER_HPP

class Arguments;
class SourceCode;
class TreeSitter;
struct TSNode;

#include <string>

class SyntaxVerifier {
  public:
    SyntaxVerifier(void);
    std::string verify(const SourceCode& source_code, TreeSitter& tree_sitter) const;

  private:
    static int walk_callback(const TSNode& node, void* user_data);
};

#endif
