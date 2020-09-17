#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

struct node;
typedef struct node Node;

struct node
{
  MY_STRING data;
  int size;
  Node* left;
  Node* right;
  int height;
};


int height(TREE hRoot);


TREE tree_init_default(void)
{
  return NULL;
}

void tree_insert(TREE* phRoot, MY_STRING value)
{
  Node* pRoot = (Node*)*phRoot;
  if(pRoot==NULL)
  {
    *phRoot = (Node*)malloc(sizeof(Node));
    if(*phRoot==NULL)
    {
      printf("Failed to allocate memory for tree_insert!");
      return;
    }
    pRoot =(Node*)*phRoot;
    pRoot->data = NULL;
    pRoot->left = NULL;
    pRoot->right = NULL;
    my_string_assignment(&(pRoot->data), value);
    pRoot->height = 1;
  }
  else if(my_string_compare(pRoot->data,value)>0)
  {
    //left
    tree_insert(&(pRoot->left),value);
    AVL_balance(phRoot);
  }
  else if(my_string_compare(pRoot->data,value)<0)
  {
    //right
    tree_insert(&(pRoot->right), value);
    pRoot->height = (height(pRoot->left) > height(pRoot->right) ?
                        height(pRoot->left) : height(pRoot->right))+1;
    AVL_balance(phRoot);
  }
  else
  {
    //equal
    increase_size(pRoot, value);
  }
}

void increase_size(TREE hRoot, MY_STRING target)
{
  Node* pRoot = (Node*)hRoot;
  if(my_string_compare(pRoot->data,target)==0)
  {
    pRoot->size++;
  }
}

int balanceFactor(TREE hRoot)
{//should be Balance factor
  Node* pRoot = (Node*) hRoot;
  if(pRoot==NULL)
  {
    return 0;
  }
  return height(pRoot->right) - height(pRoot->left);
}

int height(TREE hRoot)
{
  Node* pRoot = (Node*)hRoot;
  //int left;
  //int right;

  if(pRoot==NULL)
  {
    return 0;
  }

  //left = height(root->left);
  //right = height(root->right);
  //return (left > right ? left : right) + 1;

  return pRoot->height;
}

void AVL_balance(TREE* phRoot)
{
  Node* pRoot = (Node*) *phRoot;
  int balanceF = balanceFactor(pRoot);
  if(abs(balanceF)<2)
    return;

  if(balanceF <= -2)
  {
    //leaining left
    if(balanceFactor(pRoot->left)>0)
    {
      //left subtree leaning right
      leftRotation(&(pRoot->left));
    }
    rightRotation(phRoot);
  }
  else
  {
    //leaning right
    if(balanceFactor(pRoot->right)<0)
    {
      //right subtree leaning left
      rightRotation(&(pRoot->right));
    }
    leftRotation(phRoot);
  }
}

void leftRotation(TREE* phRoot)
{
  Node* pRoot = (Node*) *phRoot;
  Node* newRoot = pRoot->right;
  pRoot->right = newRoot->left;
  newRoot->left = pRoot;

  //update height
  pRoot->height = (height(pRoot->left) > height(pRoot->right) ?
                      height(pRoot->left) : height(pRoot->right))+1;
  newRoot->height = (height(newRoot->left) > height(newRoot->right) ?
                      height(newRoot->left) : height(newRoot->right))+1;

  //change old root pointer to new one
  *phRoot = newRoot;
}

void rightRotation(TREE* phRoot)
{
  Node* pRoot = (Node*) *phRoot;
  Node* newRoot = pRoot->left;
  pRoot->left = newRoot->right;
  newRoot->right = pRoot;

  //update height
  pRoot->height = (height(pRoot->left) > height(pRoot->right) ?
                      height(pRoot->left) : height(pRoot->right))+1;
  newRoot->height = (height(newRoot->left) > height(newRoot->right) ?
                      height(newRoot->left) : height(newRoot->right))+1;

  //change old root pointer to new one
  *phRoot = newRoot;
}

void find_biggest_size(TREE hRoot, int* size, TREE* hLargest)
{
  Node* pRoot = (Node*) hRoot;
  if(pRoot!=NULL)
  {
    if(*size == 0 || *size < pRoot->size)
    {
      *size = pRoot->size;
      *hLargest = hRoot;
    }
    find_biggest_size(pRoot->left, size, hLargest);
    find_biggest_size(pRoot->left, size, hLargest);
  }
}

MY_STRING get_key(TREE hRoot)
{
  Node* pRoot = (Node*) hRoot;
  return pRoot->data;
}

void tree_destroy(TREE* phRoot)
{
  Node* pRoot = (Node*) *phRoot;
  if(pRoot!=NULL)
  {
    tree_destroy(pRoot->left);
    tree_destroy(pRoot->right);
    free(pRoot);
    *phRoot = NULL;
  }
}
