#ifndef SYNTAX_VERIFIER_HPP
#define SYNTAX_VERIFIER_HPP

#include <arguments.hpp>
#include <tree_sitter.hpp>
#include <memory>

class SyntaxVerifier {
  public:
    Arguments* arguments;
    TreeSitter* tree_sitter;

    SyntaxVerifier(Arguments* arguments, TreeSitter* tree_sitter);
    std::string verify(void);
};

#endif
