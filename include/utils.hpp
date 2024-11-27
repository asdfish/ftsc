#ifndef UTILS_HPP
#define UTILS_HPP

#include <map>
#include <string>

template <typename key_t, typename answer_t>
answer_t safe_map_at(std::map<key_t, answer_t>& map, key_t at) {
  answer_t output;
  try {
    output = map.at(at);
  } catch(const std::exception&) {}

  return output;
}

extern size_t ansi_color_string_length(const std::string& ansi_color_string);

#endif
