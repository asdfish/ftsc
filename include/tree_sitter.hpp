#ifndef TREE_SITTER_HPP
#define TREE_SITTER_HPP

#include <tree_sitter/api.h>

#include <string>

typedef int (*)

class TreeSitter {
  public:
    TSParser* parser = NULL;
    TSTree* tree = NULL;

    TreeSitter(void);
    ~TreeSitter(void);

    void parse(const std::string& string);
    void walk();
};

#endif
