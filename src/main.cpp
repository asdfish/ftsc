#include <arguments.hpp>
#include <source_code.hpp>
#include <syntax_verifier.hpp>
#include <tree_sitter.hpp>

#include <iostream>

int main(int argc, const char* argv[]) {
  Arguments arguments = Arguments();
  if(arguments.parse(argc, argv))
    return -1;

  std::string output_message = "";

  output_message = arguments.verify();
  if(output_message.length()) {
    std::cerr << output_message << '\n';
    return -1;
  }

  SourceCode source_code = SourceCode(arguments.input_files);

  TreeSitter tree_sitter = TreeSitter();
  tree_sitter.parse(source_code);

  SyntaxVerifier syntax_verifier = SyntaxVerifier();
  output_message = syntax_verifier.verify(source_code, tree_sitter);
  if(output_message.length()) {
    std::cerr << output_message << '\n';
    return -1;
  }

  return 0;
}
