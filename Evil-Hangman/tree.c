#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

struct node;
typedef struct node Node;

struct node
{
  MY_STRING key;
  int size;
  GENERIC_VECTOR data;
  Node* left;
  Node* right;
  int height;
};


int height(TREE hRoot);

TREE tree_init_default(void)
{
  return NULL;
}

TREE tree_insert(TREE hRoot, MY_STRING Key, MY_STRING value)
{
  Node* pRoot = (Node*) hRoot;
  if(pRoot==NULL)
  {
    pRoot = (Node*)malloc(sizeof(Node));
    if(pRoot==NULL)
    {
      printf("Failed to allocate memory for tree_insert!");
      return NULL;
    }
    pRoot->key = my_string_init_default();
    pRoot->left = NULL;
    pRoot->right = NULL;
    my_string_assignment(&(pRoot->key), Key);
    pRoot->data = generic_vector_init_default();
    generic_vector_push_back(pRoot->data, value);
    pRoot->height = 1;
    pRoot->size = 1;
  }
  else if(my_string_compare(Key,pRoot->key)<0)
  {
    //left
    pRoot->left = tree_insert(pRoot->left,Key, value);
    pRoot->height = ((height(pRoot->left) > height(pRoot->right)) ?
                     height(pRoot->left) : height(pRoot->right)) + 1;
    pRoot = AVL_balance(pRoot);
  }
  else if(my_string_compare(Key,pRoot->key)>0)
  {
    //right
    pRoot->right = tree_insert(pRoot->right, Key, value);
    pRoot->height = ((height(pRoot->left) > height(pRoot->right)) ?
		     height(pRoot->left) : height(pRoot->right)) + 1;
    pRoot = AVL_balance(pRoot);
  }
  else if(my_string_compare(Key,pRoot->key)==0)
  {
    //equal
    generic_vector_push_back(pRoot->data, value);
    increase_size(hRoot, Key) ;
  }
  return pRoot;
}

void increase_size(TREE hRoot, MY_STRING target)
{
  Node* pRoot = (Node*)hRoot;
  if(my_string_compare(pRoot->key,target)==0)
  {
    pRoot->size++;
  }
}

int balanceFactor(TREE hRoot)
{
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
  if(pRoot==NULL)
  {
    return 0;
  }
  return pRoot->height;
}

TREE AVL_balance(TREE hRoot)
{
  Node* pRoot = (Node*) hRoot;
  int balanceF = balanceFactor(pRoot);
  if(abs(balanceF)<2)
    return pRoot;

  if(balanceF <= -2)
  {
    //root leaining left
    if(balanceFactor(pRoot->left)>0)
    {
      //left subtree leaning right
      pRoot->left = leftRotation(pRoot->left);
    }
    pRoot = rightRotation(pRoot);
  }
  else
  {

//    root leaning right
    if(balanceFactor(pRoot->right)<0)
    {
      //right subtree leaning left
      pRoot->right = rightRotation(pRoot->right);
    }
    pRoot = leftRotation(pRoot);
  }
  return pRoot;
}

TREE leftRotation(TREE hRoot)
{
  Node* pRoot = (Node*)hRoot;
  Node* newRoot = pRoot->right;
  Node* T2 = newRoot->left;

  newRoot->left = pRoot;
  pRoot->right  = T2;

  //update height
  pRoot->height = (height(pRoot->left) > height(pRoot->right) ?
		   height(pRoot->left) : height(pRoot->right))+1;
  newRoot->height = (height(newRoot->left) > height(newRoot->right) ?
                      height(newRoot->left) : height(newRoot->right))+1;

  //change old root pointer to new one
  return newRoot;
}

TREE rightRotation(TREE hRoot)
{
  Node* pRoot = (Node*) hRoot;
  Node* newRoot = pRoot->left;
  pRoot->left = newRoot->right;
  newRoot->right = pRoot;
  //update height
  pRoot->height = (height(pRoot->left) > height(pRoot->right) ?
                      height(pRoot->left) : height(pRoot->right))+1;
  newRoot->height = (height(newRoot->left) > height(newRoot->right) ?
                      height(newRoot->left) : height(newRoot->right))+1;

  //change old root pointer to new one
  return newRoot;
}

void swap_vector(TREE hRoot, int* pSize, MY_STRING* hLargest,  GENERIC_VECTOR* newVector)
{
    Node* pRoot = (Node*) hRoot;
    if(pRoot!=NULL)
    {
        if(*pSize == 0 || *pSize < pRoot->size)
        {
	  //	    printf("swap vectors:\n");
            GENERIC_VECTOR temp = pRoot->data;
            pRoot->data = *newVector;
            *newVector = temp;
            *pSize = pRoot->size;
	    //my_string_insertion(*hLargest,stdout);
	    my_string_assignment(hLargest, pRoot->key);
	    /*printf("   ");
	    my_string_insertion(*hLargest,stdout);
	    printf("\n");*/
        }
        swap_vector(pRoot->left, pSize,hLargest, newVector);
        swap_vector(pRoot->right, pSize, hLargest, newVector);
    }
}

void find_biggest_size(TREE hRoot, int* pSize, MY_STRING* hLargest)
{
  Node* pRoot = (Node*) hRoot;
  if(pRoot!=NULL)
  {
    if(*pSize == 0 || *pSize < pRoot->size)
    {
      *pSize = pRoot->size;
      *hLargest = pRoot->key;
    }
    find_biggest_size(pRoot->left, pSize, hLargest);
    find_biggest_size(pRoot->left, pSize, hLargest);
  }
}

void print_in_order(TREE hRoot)
{
  Node* pRoot = (Node*) hRoot;
  if(pRoot!=NULL)
  {
    print_in_order(pRoot->left);
    my_string_insertion(pRoot->key, stdout);
    printf("  %d\n",pRoot->size);
    //    generic_vector_print(pRoot->data);
    print_in_order(pRoot->right);
  }
}

MY_STRING get_key(TREE hRoot)
{
  Node* pRoot = (Node*) hRoot;
  return pRoot->key;
}

void tree_destroy(TREE* phRoot)
{
  Node* pRoot = (Node*) *phRoot;
  if(pRoot!=NULL)
  {
    tree_destroy(&(pRoot->left));
    tree_destroy(&(pRoot->right));
    my_string_destroy(&(pRoot->key));
    generic_vector_destroy(&(pRoot->data));
    free(pRoot);
    *phRoot = NULL;
  }
}
