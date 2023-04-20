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
/*Implemente la función *createTreeMap* en el archivo treemap.c. Esta función recibe la función de comparación de claves y crea un mapa (TreeMap) inicializando sus variables. 
El siguiente código muestra como inicializar la función de comparación. Reserve memoria, inicialice el resto de variables y retorne el mapa.
*/
TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap* map = (TreeMap*) malloc(sizeof(TreeMap));
    if (map==NULL)return NULL;
    map->root=NULL;
    map->current=NULL;
    map->lower_than=lower_than;
    return map;
}
/*
 Implemente la función void insertTreeMap(TreeMap * tree, void* key, void * value). Esta función inserta un nuevo dato (key,value) en el árbol y hace que el current apunte al nuevo nodo.
Para insertar un dato, primero debe realizar una búsqueda para encontrar donde debería ubicarse. Luego crear el nuevo nodo y enlazarlo. Si la clave del dato ya existe retorne sin hacer nada (recuerde que el mapa no permite claves repetidas).*/

void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode * current=tree->root;
    if (current==NULL)
    {
        //es mas eficiente crearlo en 2 partes pero solo se va crear cuando sea necesario??
        //o crearlo al principio de la funcion y si ya existe la clave se libera memoria del nodo??
        TreeNode * nuevo=createTreeNode(key,value);
        tree->root=nuevo;
        tree->current=nuevo;
        return;
    }

    int resultadoComp=0;
    TreeNode * parent=NULL;
    while (current!=NULL)
    {
        if (is_equal(tree,current->pair->key,key)==1)return;
        //tengo que actualizar el current??
        parent=current;
        resultadoComp = tree->lower_than(current->pair->key,key);
        if (resultadoComp==1) current=current->right;
        else current=current->left; 
    }
    TreeNode * nuevo=createTreeNode(key,value);
    nuevo->parent=parent;
    if (resultadoComp==1) parent->right=nuevo;
    else parent->left=nuevo;
    tree->current=nuevo;

}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

/*Implemente la función Pair* searchTreeMap(TreeMap* tree, void* key), la cual busca el nodo con clave igual a key y retorna el **Pair** asociado al nodo. Si no se encuentra la clave retorna NULL.
Recuerde hacer que el current apunte al nodo encontrado.
    */


Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode * current=tree->root;
    while (current!=NULL)
    {
        if (is_equal(tree,current->pair->key,key)==1)
        {
            tree->current=current;
            return current->pair;
        }
        int resultadoComp = tree->lower_than(current->pair->key,key);
        if (resultadoComp==1) current=current->right;
        else current=current->left;   
    }
    return NULL;
    
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
