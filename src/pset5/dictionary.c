/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dictionary.h"


/**
 * Nick Sifniotis
 * 
 * Trie structure for storing the dictionary in heap memory.
 * 
 **/
typedef struct WordTrieNode
{
    struct WordTrieNode* children[27];
    bool is_word;
} WordTrieNode;

WordTrieNode* tree_root;


/**
 * Construct a new WordTrieNode child.
 **/
WordTrieNode* new_child()
{
    WordTrieNode* res = malloc(sizeof (WordTrieNode));
    res->is_word = false;
    memset (res->children, 0, sizeof(WordTrieNode*) * 27);
    
    return res;
}


/**
 * Adds a word to the dictionary.
 **/
void add_word(const char* word)
{
    WordTrieNode* current = tree_root;
    for (char* iterator = (char*)word; *iterator != 10; iterator++)
    {
        int index;
        if (*iterator == '\'')
            index = 26;
        else
            index = (*iterator) - 'a';
        
        if (!current->children[index])
            current->children[index] = new_child();

        current = current->children[index];
    }
    
    // current is now pointing to the node that will record the existance of this word.
    current->is_word = true;
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
        return false;

    tree_root = new_child();
    
    char* buffer = calloc(sizeof (char), 47);
    while (!feof(fp))
    {
        fgets(buffer, 47, fp);
        add_word(buffer);
    }
    fclose(fp);
    free (buffer);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}


/**
 * I love the smell of recursion in the morning.
 **/
void unload_node(WordTrieNode* node)
{
    for (WordTrieNode** iterator = &(node->children[0]); iterator < &(node->children[27]); iterator ++)
        if (*iterator)
            unload_node (*iterator);

    free (node);
}


/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    unload_node (tree_root);
    return true;
}

