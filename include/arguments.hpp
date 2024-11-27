#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

extern "C" {
#include <carp/carp.h>
}

#include <array>
#include <map>
#include <string>
#include <vector>

class Arguments {
  public:
    std::map<std::string, std::string> node_colors = {
      { "ERROR",  "41" },
      { "number", "34" },
    };
    std::vector<std::string> input_files;
    std::string output_file = "a.out.js";

    Arguments(void);
    int parse(int argc, const char* argv[]);
    void print_help(void) const;
    std::string verify(void) const;

  private:
    const std::array<struct CarpOption, 4> options = {{
      { "output",     'o', true, },
      { "help",       'h', false, },
      { "node",       'n', true, },
      { "node_reset", 'N', false, },
    }};
    const std::array<std::string, 4> option_docs = {
      "Output file, defaults to a.out.js",
      "Print this message",
      "Set node type ansi color, -n \'number=40'.\n"
        "\t\tExpands to \'\\e[[VALUE]m\'\n"
        "\t\tSee arguments.hpp for defaults.\n",
      "Reset node_colors to empty"
    };

    static int parser_callback(char flag_short, enum CarpArgumentType argument_type, const char* argument, void* user_data);
};

#endif
