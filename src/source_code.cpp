#include <source_code.hpp>

#include <cmath>
#include <cstring>
#include <iostream>
#include <fstream>

SourceCode::SourceCode(void) {}
SourceCode::SourceCode(const std::string& path) {
  set_contents(file_contents(path));
}
SourceCode::SourceCode(const std::vector<std::string>& paths) {
  std::string contents_buffer;
  for(const std::string& path: paths)
    contents_buffer += file_contents(path) + "\n";

  set_contents(contents_buffer);
}
SourceCode::SourceCode(const std::filesystem::path& path) {
  set_contents(file_contents(path));
}
SourceCode::SourceCode(const std::vector<std::filesystem::path>& paths) {
  std::string contents_buffer;
  for(const std::filesystem::path& path: paths)
    contents_buffer += file_contents(path) + "\n";

  set_contents(contents_buffer);
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

std::string SourceCode::file_contents(const std::filesystem::path& path) {
  std::ifstream file = std::ifstream(path);
  if(!file.good())
    return "";

  std::stringstream file_buffer;
  file_buffer << file.rdbuf();

  return file_buffer.str();
}
