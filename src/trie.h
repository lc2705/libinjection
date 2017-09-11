#include <stdbool.h>
#include <limits.h>

struct trie {
    void* val; 
    struct trie* children[256]; 
    enum {
        trienode_leaf = 0, 
        trienode_twig,
        trienode_branch
    } type; 
};

struct trie* trie_create();

void* trie_insert(struct trie* data, const char* key, int len, void* val);

void* trie_lookup(struct trie* data, const char* key, int len);

void trie_remove(struct trie* data, char* key);

void trie_destroy(struct trie* data);
