#include <string.h>

#include "include/dtstructs.h"

static void tree_internal_max_depth(tree_t tree, size_t* current_max_depth, size_t current_depth)
{
    if(current_depth >= *current_max_depth) *current_max_depth = current_depth;

    for (size_t i = 0; i < tree->leaf_count; i++)
    {
        tree_internal_max_depth(tree->leafs[i], current_max_depth, current_depth + 1);
    }
}

size_t tree_max_depth(tree_t tree)
{
    size_t max_depth = 0;

    tree_internal_max_depth(tree, &max_depth, 0);
    
    return max_depth;
}

size_t tree_child_count(tree_t tree)
{
    return tree->leaf_count;
}

tree_t tree_raw_create(size_t data_size, void* data)
{
    tree_t tree = malloc(sizeof(tree_node_t) + data_size);
    tree->leafs = NULL;
    tree->leaf_count = 0;

    if(data != NULL) memcpy(tree->data, data, data_size);
    
    return tree;
}

void* tree_raw_value(tree_t tree)
{
    return tree->data;
}

tree_t tree_raw_insert(tree_t tree, size_t data_size, void* data)
{
    tree->leaf_count++;
    tree->leafs = realloc(tree->leafs, sizeof(tree_t) * tree->leaf_count);
    tree->leafs[tree->leaf_count - 1] = tree_raw_create(data_size, data);
    return tree->leafs[tree->leaf_count - 1];
}

void tree_insert_subtree(tree_t tree, tree_t subtree)
{
    tree->leaf_count++;
    tree->leafs = realloc(tree->leafs, sizeof(tree_t) * tree->leaf_count);
    tree->leafs[tree->leaf_count - 1] = subtree; 
}

void tree_remove_subtree(tree_t tree, size_t subtree_index)
{
    tree_free(tree->leafs[subtree_index]);

    for (size_t i = subtree_index; i < tree->leaf_count - 1; i++)
    {
        tree->leafs[i] = tree->leafs[i + 1];
    }

    tree->leaf_count--;
    tree->leafs = realloc(tree->leafs, sizeof(tree_t) * tree->leaf_count);
}

tree_t tree_get_subtree(tree_t tree, size_t subtree_index)
{
    if(tree->leaf_count <= subtree_index) return NULL;

    return tree->leafs[subtree_index];
}

void tree_free(tree_t tree)
{
    for (size_t i = 0; i < tree->leaf_count; i++)
        tree_free(tree->leafs[i]);

    if(tree->leafs != NULL)
        free(tree->leafs);
    
    free(tree);
}