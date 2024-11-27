#include <utils.hpp>

#include <cstring>

size_t ansi_color_string_length(const std::string& ansi_color_string) {
  size_t length = ansi_color_string.length();

  char* string_p = (char*) ansi_color_string.c_str();

  while((string_p = strstr(string_p, "\e"))) {
    length --;

    char* string_p_p = string_p;
    if((string_p_p = strstr(string_p, "m")))
      length -= string_p_p - string_p;

    string_p ++;
  }

  return length;
}
