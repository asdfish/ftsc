#include <arguments.hpp>

#include <iostream>

int main(int argc, const char* argv[]) {
  int result = 0;
  Arguments arguments = Arguments(argc, argv, &result);

  if(result != 0) {
    if(result < 0)
      std::cerr << "Failed to parse arguments\n";
    return result;
  }

  std::string message = arguments.verify();
  if(message.length()) {
    std::cerr << message << '\n';
    return -1;
  }
  return 0;
}
