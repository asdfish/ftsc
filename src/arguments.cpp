#include <arguments.hpp>

#include <iostream>
#include <vector>

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

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
      }
      break;
    case KEY:
      arguments->input_files.push_back(argument);
      break;
  }

  return 0;
}

Arguments::Arguments(int argc, const char* argv[], int* result) {
  const struct CarpOption options[] = {
    { "output", 'o', true },
  };
  
  input_files.reserve(argc);

  if(result)
    *result = carp_parse(argc, argv, options, ARRAY_LENGTH(options), callback, this);
  else
    carp_parse(argc, argv, options, ARRAY_LENGTH(options), callback, this);
}
