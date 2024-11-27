#ifndef TREE_SITTER_HPP
#define TREE_SITTER_HPP

#include <source_code.hpp>

#include <tree_sitter/api.h>

#include <functional>
#include <string>

class TreeSitter {
  public:
    TSParser* parser = NULL;
    TSTree* tree = NULL;

    TreeSitter(void);
    ~TreeSitter(void);

    void parse(const SourceCode& source_code);
    void parse(const std::string& string);
    int walk(std::function<int(const TSNode& node, void* user_data)> callback, void* user_data);
};

#endif
