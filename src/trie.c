#include <stdio.h>
#include <stdlib.h>

#include "trie.h"

struct trie* trie_create()
{
    return calloc(1, sizeof(struct trie));
}

void* trie_traverse(struct trie* data, const char* key, int len)
{
    struct trie* current_node = data;
    size_t key_n;
    while (len)
    {
        struct trie* next_node;
        if(*key >= 'a' && *key <= 'z')
            key_n = (size_t)*key - 'a' + 'A';
        else 
            key_n = (size_t)*key;
        if(key_n > 255)
            return NULL;

        next_node = current_node->children[key_n];

        if (!next_node) 
        {
            return NULL;
        }

        current_node = next_node;

        key++;
        len--;
    }

    return current_node;
}

void* trie_insert(struct trie* data, const char* key, int len, void* val)
{
    struct trie* current_node = data;

    while (len)
    {
        struct trie* next_node = current_node->children[(size_t)*key];
        if(current_node->type == trienode_twig) {
            if(!next_node) 
                current_node->type++;
        } else if (current_node->type == trienode_leaf) {
            current_node->type++;
        }        
/*
        switch (current_node->type)
        {
            case trienode_twig:
                if (next_node)
                {
                    break;
                }
            case trienode_leaf:
                current_node->type++;
        }
*/
        if (!next_node) 
        {
            current_node->children[(size_t)*key] = trie_create();
            next_node = current_node->children[(size_t)*key];
            if (trienode_twig == current_node->type)
            {
                *current_node->children = next_node;
            }
        }

        current_node = next_node;

        key++;
        len--;
    }

    current_node->val = val;

    return current_node;
}

void* trie_lookup(struct trie* data, const char* key, int len)
{   
    struct trie* current_node = trie_traverse(data, key, len);

    if (!current_node)
    {
        return NULL;
    }

    return current_node->val;
}
void trie_remove(struct trie* data, char* key)
{
    struct trie* current_node = data;

    while (*key != 0)
    {
        struct trie* next_node = current_node->children[(size_t)*key];

        if (!next_node) 
        {
            return;
        }

        current_node = next_node;

        key++;
    }

    free(current_node->val);
    return;
}

void trie_destroy(struct trie* data)
{
    int a;
    for (a = 1; a < 256; a++)
    {
        if (data->children[a])
        {
            trie_destroy(data->children[a]);
        }
    }

    free(data);
    return;
}
