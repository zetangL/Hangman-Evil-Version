#include <stdio.h>
#include <stdlib.h>
#include "generic_vector.h"

struct vector
{
  int size;
  int capacity;
  Item* data;
};
typedef struct vector Vector;


GENERIC_VECTOR generic_vector_init_default(void)
{
  Vector* pVector;
  int i;
  pVector = (Vector*) malloc(sizeof(Vector));
  if(pVector!=NULL)
  {
    pVector->size = 0;
    pVector->capacity = 1;
    pVector->data = (Item*)malloc(sizeof(Item)
        * pVector->capacity);
    if(pVector->data==NULL)
    {
      free(pVector);
      return NULL;
    }
    for(i=0; i<pVector->capacity; i++)
    {
      pVector->data[i] = NULL;
    }
  }
  return pVector;
}

int generic_vector_get_size(GENERIC_VECTOR hVector)
{
  Vector* pVector = (Vector*) hVector;
  return pVector->size;
}
int generic_vector_get_capacity(GENERIC_VECTOR hVector)
{
  Vector* pVector = (Vector*) hVector;
  return pVector->capacity;
}

Item* generic_vector_at(GENERIC_VECTOR hVector, int index)
{
  Vector* pVector = hVector;
  if(index < 0 || index > pVector->size)
    return NULL;
  return &(pVector->data[index]);
}

Status generic_vector_push_back(GENERIC_VECTOR hVector, Item pItem)
{
  Vector* pVector = (Vector*)hVector;
  Item* temp;
  int i;
  //check if need resize
  if(pVector->size >= pVector->capacity)
  {
    temp = (Item*)malloc(sizeof(Item)
        *(((pVector->capacity*4)/3)+1));
    //check malloc failed
    if(temp == NULL)
    {
      return FAILURE;
    }
    //if temp successfully malloc, NULL out all elements
    for(i=0; i<((pVector->capacity*4)/3)+1; i++)
    {
      temp[i] = NULL;
    }
    //copy elements from previous array to new one
    for(i=0; i<pVector->size; i++)
    {
      my_string_assignment(&temp[i], pVector->data[i]);
      //check if assignment failed
      if(temp[i]==NULL)
      {
        free(temp);
	printf("Assignment failed\n");
        return FAILURE;
      }
    }
    pVector->capacity = ((pVector->capacity*4)/3)+1;
    //destroy previous array
    for(i=0; i<pVector->size; i++)
    {
      my_string_destroy(&pVector->data[i]);
    }
    free(pVector->data);
    //set previous array pointer = current array
    pVector->data = temp;
  }
  my_string_assignment(&pVector->data[pVector->size], pItem);
  pVector->size++;
  return SUCCESS;
}

Status generic_vector_pop_back(GENERIC_VECTOR hVector)
{
  Vector* pVector = (Vector*)hVector;
  if(pVector->size <= 0)
  {
    return FAILURE;
  }
  my_string_destroy(&pVector->data[pVector->size-1]);
  pVector->size--;
  return SUCCESS;
}
GENERIC_VECTOR generic_vector_copy_key(GENERIC_VECTOR hVector, MY_STRING hKey)
{
  Vector* pVector = (Vector*)hVector;
  int i;
  Vector* pTemp = generic_vector_init_default();
  for(i=0; i<pVector->size; i++)
  {
    if(is_same_key(pVector->data[i],hKey))
    {
        generic_vector_push_back(pTemp, pVector->data[i]);
    }
  }
  return pTemp;
}

void generic_vector_print(GENERIC_VECTOR hVector)
{
  Vector* pVector = (Vector*)hVector;
  int i;
  for(i = 0 ; i<pVector->size; i++)
  {
    my_string_insertion(pVector->data[i],stdout);
    printf("\n");
  }
}

void generic_vector_destroy(GENERIC_VECTOR* phVector)
{
  Vector* pVector = (Vector*)*phVector;
  int i;
  for(i=0; i<pVector->size;i++)
  {
      my_string_destroy(&pVector->data[i]);
  }
  free(pVector->data);
  free(pVector);
  *phVector = NULL;
}
