#ifndef SOURCE_CODE_HPP
#define SOURCE_CODE_HPP

#include <string>
#include <vector>

class SourceCode {
  public:
    std::string contents;
    std::vector<size_t> newlines;

    SourceCode(void);
    ssize_t line_number(size_t char_index);
    void set_contents(const std::string& contents);
};

#endif
