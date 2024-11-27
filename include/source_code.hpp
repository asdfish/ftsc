#ifndef SOURCE_CODE_HPP
#define SOURCE_CODE_HPP

#include <filesystem>
#include <string>
#include <vector>

class SourceCode {
  public:
    std::string contents;
    std::vector<size_t> newlines;

    SourceCode(void);
    SourceCode(const std::string& path);
    SourceCode(const std::vector<std::string>& paths);
    SourceCode(const std::filesystem::path& path);
    SourceCode(const std::vector<std::filesystem::path>& paths);

    ssize_t get_line_number(size_t char_index) const;
    void set_contents(const std::string& contents);

  private:
    std::string get_file_contents(const std::filesystem::path& path) const;
};

#endif
