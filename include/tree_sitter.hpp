#ifndef TREE_SITTER_HPP
#define TREE_SITTER_HPP

class SourceCode;

typedef struct TSLanguage TSLanguage;
typedef struct TSNode TSNode;
typedef struct TSParser TSParser;
typedef struct TSTree TSTree;

#include <functional>
#include <string>

class TreeSitter {
  public:
    const TSLanguage* language = NULL;
    TSParser* parser = NULL;
    TSTree* tree = NULL;

    TreeSitter(void);
    ~TreeSitter(void);

    void parse(const SourceCode& source_code);
    void parse(const std::string& string);
    int walk(std::function<int(const TSNode& node, void* user_data)> callback, void* user_data) const;
};

#endif
