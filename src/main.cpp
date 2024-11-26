#include <arguments.hpp>
#include <tree_sitter.hpp>
#include <syntax_verifier.hpp>

#include <iostream>

int main(int argc, const char* argv[]) {
  int result = 0;
  Arguments arguments = Arguments(argc, argv, &result);

  if(result != 0) {
    if(result < 0)
      std::cerr << "Failed to parse arguments\n";
    return result;
  }

  std::string verify_message = "";

  verify_message = arguments.verify();
  if(verify_message.length()) {
    std::cerr << verify_message << '\n';
    return -1;
  }

  TreeSitter tree_sitter = TreeSitter();

  SyntaxVerifier syntax_verifier = SyntaxVerifier(&arguments, &tree_sitter);
  verify_message = syntax_verifier.verify();
  if(verify_message.length()) {
    std::cerr << verify_message << '\n';
    return -1;
  }

  return 0;
}
