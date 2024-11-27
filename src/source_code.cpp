#include <arguments.hpp>
#include <source_code.hpp>
#include <tree_sitter.hpp>

#include <cmath>
#include <cstring>
#include <fstream>

SourceCode::SourceCode(void) {}
SourceCode::SourceCode(const std::string& path) {
  set_contents(get_file_contents(path));
}
SourceCode::SourceCode(const std::vector<std::string>& paths) {
  std::string contents_buffer;
  for(const std::string& path: paths)
    contents_buffer += get_file_contents(path) + "\n";

  set_contents(contents_buffer);
}
SourceCode::SourceCode(const std::filesystem::path& path) {
  set_contents(get_file_contents(path));
}
SourceCode::SourceCode(const std::vector<std::filesystem::path>& paths) {
  std::string contents_buffer;
  for(const std::filesystem::path& path: paths)
    contents_buffer += get_file_contents(path) + "\n";

  set_contents(contents_buffer);
}
size_t SourceCode::get_line_number(size_t char_index) const {
  if(!newlines.size())
    return 0;

  ssize_t low = 0;
  ssize_t high = newlines.size();

  while(low <= high) {
    ssize_t mid = ((high - low) / 2) + low;

    if(newlines[mid] == char_index)
      return (size_t) mid;

    if(newlines[mid] > char_index)
      high = mid - 1;
    else
      low = mid + 1;
  }

  return (size_t) low;
}
void SourceCode::set_contents(const std::string& contents) {
  newlines.clear();

  const char* contents_str = contents.c_str();
  if(!contents_str)
    return;

  char* contents_p = (char*) contents_str;
  while((contents_p = strstr(contents_p, "\n"))) {
    newlines.push_back(contents_p - contents_str);
    contents_p ++;
  }

  this->contents = contents;
}

std::string SourceCode::get_file_contents(const std::filesystem::path& path) const {
  std::ifstream file = std::ifstream(path);
  if(!file.good())
    return "";

  std::stringstream file_buffer;
  file_buffer << file.rdbuf();

  return file_buffer.str();
}
