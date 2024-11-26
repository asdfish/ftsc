#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <carp.h>

#include <string>
#include <vector>

class Arguments {
  public:
    std::vector<std::string> input_files;
    std::string output_file = "a.out.js";

    Arguments(int argc, const char* argv[], int* result);
};

#endif
