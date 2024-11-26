#ifndef TREE_SITTER_HPP
#define TREE_SITTER_HPP

#include <tree_sitter/api.h>

class TreeSitter {
  public:
    TSParser* parser = NULL;

    TreeSitter(void);
    ~TreeSitter(void);
};

#endif
