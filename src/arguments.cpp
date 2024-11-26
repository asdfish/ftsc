#include <arguments.hpp>

#include <iostream>
#include <filesystem>
#include <vector>

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

static const struct CarpOption options[] = {
  { "output", 'o', true },
  { "help",   'h', false },
};
static const std::vector<std::string> options_docs = {
  "Output file. Defaults to a.out.js",
  "Print this message",
};

static void print_help(void) {
  std::cout << "ftsc: Fast typescript compiler\n"
    "Usage: ftsc [INPUT_FILES...] [OPTIONS...]\n"
    "Options:\n";
  for(size_t i = 0; i < ARRAY_LENGTH(options); i ++)
    std::cout << "\t-" << options[i].flag_short << " --" << options[i].flag_long << " : " << options_docs[i] << '\n';
}

static int callback(char flag_short, enum CarpArgumentType argument_type, const char* argument, void* user_data) {
  Arguments* arguments = (Arguments*) user_data;

  switch(argument_type) {
    case FLAG:
      switch(flag_short) {
        case 'o':
          if(!argument) {
            std::cerr << "Missing argument for flag 'o'\n";
            return -1;
          }
          arguments->output_file = argument;
          break;
        case 'h':
          print_help();
          return 1;
      }
      break;
    case KEY:
      arguments->input_files.push_back(argument);
      break;
  }

  return 0;
}

Arguments::Arguments(int argc, const char* argv[], int* result) {
  input_files.reserve(argc);

  if(result)
    *result = carp_parse(argc, argv, options, ARRAY_LENGTH(options), callback, this);
  else
    carp_parse(argc, argv, options, ARRAY_LENGTH(options), callback, this);
}
std::string Arguments::verify(void) {
  if(!input_files.size())
    return "No input files provided";
  for(const std::string& input_file : input_files)
    if(!std::filesystem::is_regular_file(input_file))
      return "File \'" + input_file + "\' does not exist or is not a file";

  return "";
}
