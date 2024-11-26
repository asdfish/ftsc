#include <arguments.hpp>

#include <iostream>

int main(int argc, const char* argv[]) {
  int result = 0;
  Arguments arguments = Arguments(argc, argv, &result);
  return 0;
}
