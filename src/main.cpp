#include <carp.h>
#include <stdio.h>

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

struct Arguments {
  const char* output_file;
};

static const struct CarpOption options[] = {
  { "output", 'o', true },
};

static int parser_callback (char flag_short, enum CarpArgumentType argument_type, const char* argument, void* user_data) {
  struct Arguments* arguments = (struct Arguments*) user_data;

  switch(argument_type) {
    case FLAG:
      switch(flag_short) {
        case 'o':
          if(!argument) {
            printf("Missing argument for -o\n");
            return -1;
          }
          arguments->output_file = argument;
          break;
      }
      break;
    case KEY:
      break;
  }

  return 0;
}

int main(int argc, const char* argv[]) {
  struct Arguments arguments;
  arguments.output_file = "a.out.js";

  if(carp_parse(argc, argv, options, ARRAY_LENGTH(options), parser_callback, (void*) &arguments) != 0)
    return -1;

  printf("%s\n", arguments.output_file);
  return 0;
}
