#include <arguments.hpp>
#include <source_code.hpp>
#include <syntax_verifier.hpp>
#include <tree_sitter.hpp>

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

  SourceCode source_code = SourceCode(arguments.input_files);

  TreeSitter tree_sitter = TreeSitter();
  tree_sitter.parse(source_code);

  SyntaxVerifier syntax_verifier = SyntaxVerifier();
  verify_message = syntax_verifier.verify(source_code, tree_sitter);
  if(verify_message.length()) {
    std::cerr << verify_message << '\n';
    return -1;
  }

  return 0;
}
