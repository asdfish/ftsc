#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <carp.h>

#include <array>
#include <string>
#include <vector>

class Arguments {
  public:
    std::vector<std::string> input_files;
    std::string output_file = "a.out.js";

    Arguments(int argc, const char* argv[], int* result);
    void print_help(void) const;
    std::string verify(void) const;
  private:
    const std::array<struct CarpOption, 2> options = {
      (struct CarpOption) { "output", 'o', true, },
      (struct CarpOption) { "help",   'h', false, },
    };
    const std::array<std::string, 2> option_docs = {
      "Output file, defaults to a.out.js",
      "Print this message"
    };
    static int parser_callback(char flag_short, enum CarpArgumentType argument_type, const char* argument, void* user_data);
};

#endif
