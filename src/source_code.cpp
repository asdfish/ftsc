#include <source_code.hpp>

#include <cmath>
#include <cstring>
#include <iostream>

SourceCode::SourceCode(void) {
  set_contents(contents);
}

ssize_t SourceCode::line_number(size_t char_index) {
  if(!newlines.size())
    return 0;

  ssize_t low = 0;
  ssize_t high = newlines.size();

  while(low <= high) {
    ssize_t mid = ((high - low) / 2) + low;

    if(newlines[mid] == char_index)
      return mid;

    if(newlines[mid] > char_index)
      high = mid - 1;
    else
      low = mid + 1;
  }

  return low;
}

void SourceCode::set_contents(const std::string& contents) {
  newlines.clear();

  const char* contents_str = contents.c_str();

  char* contents_p = (char*) contents_str;
  while((contents_p = strstr(contents_p, "\n"))) {
    newlines.push_back(contents_p - contents_str);
    contents_p ++;
  }

  this->contents = contents;
}
