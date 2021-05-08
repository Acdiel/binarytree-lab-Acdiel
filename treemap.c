#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;

struct TreeNode {
    void* key;
    void * value;
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
    new->key = key;
    new->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

  TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
  
  new->root=0;
  new->current=0;
  
  new->lower_than = lower_than;
    
    //new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {

  TreeNode * aux= tree->root;
  TreeNode * n = createTreeNode(key,value);

while(aux->left!=NULL || aux->right!=NULL){
  if (tree->lower_than(key, aux->key) == 1){
       aux = aux->left;
  }else{
    if (tree->lower_than(key, aux->key) == 0)
        aux = aux->right;
      }
  }

if(is_equal(tree, aux->key, key) == 0){
if(tree->lower_than(key, aux->key) == 1 ){
aux->left = n;
n->parent = aux;
tree->current=n;
}else{
  aux->right = n;
  n->parent = aux;
  tree->current=n;
}
}
}

TreeNode * minimum(TreeNode * x){

while (x->left!=NULL){
  x = x->left;
}

    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




void * searchTreeMap(TreeMap * tree, void* key) {

  TreeNode * aux= tree->root;

  while(aux!=NULL){
    if (is_equal(tree,aux->key,key)== 1){
      tree->current=aux;
      return aux->value;
    }
    if (tree->lower_than(key, aux->key) == 1){
       aux = aux->left;
    }else{
        aux = aux->right;
      }
    }
  
    
    return NULL;
}


void * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

void * firstTreeMap(TreeMap * tree) {

  TreeNode * aux= tree->root;
  
while (aux->left!=NULL){
  aux = aux->left;
}
    return aux->key;
}

void * nextTreeMap(TreeMap * tree) {

  TreeNode * aux= tree->root;

 if (aux->right != NULL) {
   
        aux= aux->right;
        tree->current=aux;
 }

    return aux->right->key;
}
