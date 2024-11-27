#ifndef UTILS_HPP
#define UTILS_HPP

#include <map>
template <typename key_t, typename answer_t>
answer_t safe_map_at(std::map<key_t, answer_t>& map, key_t at) {
  answer_t output;
  try {
    output = map.at(at);
  } catch(const std::exception&) {}

  return output;
}

#endif
