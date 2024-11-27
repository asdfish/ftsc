#ifndef SYNTAX_VERIFIER_HPP
#define SYNTAX_VERIFIER_HPP

#include <arguments.hpp>
#include <source_code.hpp>
#include <tree_sitter.hpp>

class SyntaxVerifier {
  public:
    SyntaxVerifier(void);
    std::string verify(const SourceCode& source_code, TreeSitter& tree_sitter) const;

  private:
    static int walk_callback(const TSNode& node, void* user_data);
};

#endif
