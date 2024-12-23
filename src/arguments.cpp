#include <arguments.hpp>

#include <cstring>
#include <iostream>
#include <filesystem>

Arguments::Arguments(void) {}
int Arguments::parse(int argc, const char* argv[]) {
  input_files.reserve(argc);

  return carp_parse(argc, argv, &options[0], options.size(), parser_callback, this);
}
void Arguments::print_help(void) const {
  std::cout << "ftsc: Fast typescript compiler\n"
    "Usage: ftsc [INPUT_FILES...] [OPTIONS...]\n"
    "Options:\n";
  for(size_t i = 0; i < options.size(); i ++)
    std::cout << "\t-" << options[i].flag_short << " --" << options[i].flag_long << " : " << option_docs[i] << '\n';
}
std::string Arguments::verify(void) const {
  if(!input_files.size())
    return "No input files provided";
  for(const std::string& input_file : input_files)
    if(!std::filesystem::is_regular_file(input_file))
      return "File \'" + input_file + "\' does not exist or is not a file";

  return "";
}

int Arguments::parser_callback(char flag_short, enum CarpArgumentType argument_type, const char* argument, void* user_data) {
  Arguments* arguments = (Arguments*) user_data;

  switch(argument_type) {
    case FLAG:
      switch(flag_short) {
        case 'N':
          arguments->node_colors.clear();
          break;
        case 'o':
          if(!argument) {
            std::cerr << "Missing argument for flag 'o'\n";
            return -1;
          }
          arguments->output_file = argument;
          break;
        case 'h':
          arguments->print_help();
          return 1;
        case 'n':
          if(!argument) {
            std::cerr << "Missing argument for flag 'n'\n";
            return -1;
          }

          char* split = (char*) strstr(argument, "=");
          if(!split) {
            std::cerr << "Missing value for flag 'n'.\n"
              "See ftsc -h for usage.\n";
            return -1;
          }

          *split = '\0';
          if(!strlen(argument) || !strlen(split + 1)) {
            std::cerr << "Missing value for flag 'n'.\n"
              "See ftsc -h for usage.\n";
            return -1;
          }

          arguments->node_colors[std::string(argument)] = std::string(split + 1);
          break;
      }
      break;
    case KEY:
      arguments->input_files.push_back(argument);
      break;
  }

  return 0;
}
