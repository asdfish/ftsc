#ifndef SYNTAX_VERIFIER_HPP
#define SYNTAX_VERIFIER_HPP

#include <arguments.hpp>
#include <memory>

class SyntaxVerifier {
  public:
    Arguments* arguments;

    SyntaxVerifier(Arguments* arguments);
    std::string verify(void);
};

#endif
