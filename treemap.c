#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap* map = (TreeMap*) malloc(sizeof(TreeMap));
    if (map == NULL)return NULL;
    map->root = NULL;
    map->current = NULL;
    map->lower_than = lower_than;
    return map;
}

void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode * current = tree->root;
    if (current == NULL)
    {
        TreeNode * nuevo = createTreeNode(key,value);
        tree->root = nuevo;
        tree->current = nuevo;
        return;
    }

    int resultadoComp = 0;
    TreeNode * parent = NULL;
    while (current != NULL)
    {
        if (is_equal(tree,current->pair->key,key))return;
        parent = current;
        resultadoComp = tree->lower_than(current->pair->key,key);
        if (resultadoComp == 1)current = current->right;
        else current = current->left; 
    }
    TreeNode * nuevo = createTreeNode(key,value);
    nuevo->parent = parent;
    if (resultadoComp == 1) parent->right = nuevo;
    else parent->left = nuevo;
    tree->current = nuevo;
}

TreeNode * minimum(TreeNode * x){
    if (x->left == NULL)return x;
    TreeNode * current = x;
    while (current != NULL)
    {
        if (current->left == NULL)break;
        current = current->left;
    }
    return current;
}

void removeNode(TreeMap * tree, TreeNode* node) {
    if (node->left == NULL && node->right == NULL)
    {
        if (node->parent->right == node)node->parent->right = NULL;
        else node->parent->left = NULL;
        free(node);
        return;
    }
    if (node->left != NULL && node->right != NULL)
    {
        TreeNode * menorSubDerecho = minimum(node->right);
        node->pair = menorSubDerecho->pair;
        removeNode(tree,menorSubDerecho);
        return;
    }
    TreeNode * hijo = (node->left != NULL) ? node->left : node->right;
    if (node->parent == NULL)tree->root = hijo;
    if (node == node->parent->left)node->parent->left = hijo;
    node->parent->right = hijo;
    hijo->parent = node->parent;
    free(node);
    return;
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;
    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree,node);
}

Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode * current = tree->root;
    TreeNode * parent = NULL;
    while (current != NULL)
    {
        if (is_equal(tree,current->pair->key,key))
        {
            tree->current = current;
            return current->pair;
        }
        parent = current;
        int resultadoComp = tree->lower_than(current->pair->key,key);
        if (resultadoComp == 1) current = current->right;
        else current = current->left;   
    }
    tree->current = parent;
    return NULL;
    
}

Pair * upperBound(TreeMap * tree, void* key) {
    Pair* buscado = searchTreeMap(tree,key);
    if (buscado != NULL) return buscado;
    if (!tree->lower_than(tree->current->pair->key,key))return tree->current->pair;
    Pair* next = nextTreeMap(tree);
    if (next != NULL) return next;
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    if (tree->root == NULL)return NULL;
    TreeNode * current = tree->root;
    while (current->left != NULL)
    {
        current = current->left;    
    }
    tree->current = current;
    return current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->current == NULL)return NULL;
    if (tree->current->right != NULL)
    {
        TreeNode * minimo = minimum(tree->current->right);
        tree->current = minimo;
        return minimo->pair;
    }
    TreeNode * current = tree->current;
    while (current != NULL)
    {
        if (current->parent != NULL && tree->lower_than(current->pair->key,current->parent->pair->key))
        {
            tree->current = current->parent;
            return current->parent->pair;
        }
        current = current->parent;    
    }
    return NULL;
}