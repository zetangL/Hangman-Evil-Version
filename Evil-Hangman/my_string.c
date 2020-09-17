#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"

struct my_string
{
  int size;
  int capacity;
  char* data;
};
typedef struct my_string My_string;


MY_STRING my_string_init_default(void)
{
  My_string* pMy_string;
  pMy_string = (My_string*)malloc(sizeof(My_string));
  if(pMy_string != NULL)
  {
    pMy_string->size = 0;
    pMy_string->capacity = 7;
    pMy_string->data = malloc(sizeof(char)* 7);
    if(pMy_string->data == NULL)
    {
      printf("Failed to allocate memory for data character array!\n");
      return NULL;
    }
  }
  return pMy_string;
}

MY_STRING my_string_init_c_string(const char* c_string)
{
  int i;
  int count = 0;
  My_string* pMy_string = (My_string*)malloc(sizeof(My_string));
  while(c_string[count] != '\0')
  {
    count++;
  }
  if(pMy_string!=NULL)
  {
    pMy_string->size = count;
    pMy_string->capacity = count+1;
    pMy_string->data = malloc(sizeof(char)*pMy_string->capacity);
    if(pMy_string->data==NULL)
    {
      printf("Failed to allocate memory for data character array!\n");
      free(pMy_string);
      return NULL;
    }
    else
    {
      for(i=0; i<=count; i++)
      {
        pMy_string->data[i] = c_string[i];
      }
    }
  }
  return pMy_string;

}

//accessors
int my_string_get_capacity(MY_STRING hMy_string)
{
  My_string* pMy_string = (My_string*)hMy_string;
  return pMy_string->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
  My_string* pMy_string = (My_string*)hMy_string;
  return pMy_string->size;
}

//Extractction
Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
  char c;
  char* temp;
  int index = 0;
  My_string* pMy_string = (My_string*) hMy_string;
  //clear size and data in the string
  pMy_string->size = 0;

  c = fgetc(fp);
  while(isspace(c))
  {
    c = fgetc(fp);
  }
  if(c==EOF)
  {
    return FAILURE;
  }
  while(c!=EOF && !isspace(c))
  {
    pMy_string->data[index] = c;
    pMy_string->size++;
    index++;
    if(pMy_string->size >= pMy_string->capacity)
    {
      temp = realloc(pMy_string->data, (pMy_string->capacity)*2+1);
      if(temp==NULL)
      {
        return FAILURE;
      }
      pMy_string->data = temp;
      pMy_string->capacity = (pMy_string->capacity)*2+1;
    }
    c = fgetc(fp);
  }
  ungetc(c, fp);
  //pMy_string->data[index] = '\0';
  return SUCCESS;
}

//Insertion
Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
  My_string* pMy_string = (My_string*) hMy_string;
  int i;
  for(i=0; i<pMy_string->size; i++)
  {
    fprintf(fp, "%c", pMy_string->data[i]);
  }
  return SUCCESS;
}

//Lab 4
//Push
Status my_string_push_back(MY_STRING hMy_string, char item)
{
  My_string* pMy_string = (My_string*) hMy_string;
  char* temp;
  if(pMy_string->size+1 >= pMy_string->capacity)
  {
    temp = realloc(pMy_string->data, (pMy_string->capacity)*2+1);
    if(temp==NULL)
    {
      return FAILURE;
    }
    pMy_string->data = temp;
    pMy_string->capacity = (pMy_string->capacity)*2+1;
  }
  pMy_string->data[pMy_string->size]= item;
  pMy_string->size++;
  //pMy_string->data[pMy_string->size] = '\0';
  return SUCCESS;
}

//Pop
Status my_string_pop_back(MY_STRING hMy_string)
{
  My_string* pMy_string = (My_string*) hMy_string;
  if(pMy_string->size<=0)
  {
    return FAILURE;
  }
  pMy_string->size--;
  //pMy_string->data[pMy_string->size] = '\0';
  return SUCCESS;
}

//at
char* my_string_at(MY_STRING hMy_string, int index)
{
  My_string* pMy_string = (My_string*)hMy_string;
  if(index >= pMy_string->size)
  {
    return NULL;
  }
  return &(pMy_string->data[index]);
}

//return as c-string
char* my_string_c_str(MY_STRING hMy_string)
{
  My_string* pMy_string = (My_string*)hMy_string;
  char* temp;
  if(pMy_string->size+1 > pMy_string->capacity)
  {
    temp = realloc(pMy_string->data, (pMy_string->capacity)+1);
    pMy_string->data = temp;
    pMy_string->capacity = (pMy_string->capacity)+1;
  }
  pMy_string->data[pMy_string->size] = '\0';
  return pMy_string->data;
}

//concat
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
  My_string* pResult = (My_string*) hResult;
  My_string* pAppend = (My_string*) hAppend;
  char* temp;
  int i;
  //if size in result is not enough for both reallocate enough memory
  if((pResult->size + pAppend->size) >= pResult->capacity)
  {
    temp = realloc(pResult->data, (pResult->capacity + pAppend->capacity));
    if(temp==NULL)
    return FAILURE;
    pResult->data = temp;
    pResult->capacity = pResult->capacity + pAppend->capacity;
  }
  for(i=0; i<pAppend->size; i++)
  {
    pResult->data[pResult->size] = pAppend->data[i];
    pResult->size++;
  }
  return SUCCESS;
}

//isEmpty?
Boolean my_string_empty(MY_STRING hMy_string)
{
  My_string* pMy_string = (My_string*) hMy_string;
  if(pMy_string->size <=0)
  {
    return TRUE;
  }
  return FALSE;
}

//compare
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
  int i = 0;
  My_string* pLeft_string = (My_string*)hLeft_string;
  My_string* pRight_string = (My_string*)hRight_string;
  while(i<pLeft_string->size && (pLeft_string->data[i]==pRight_string->data[i]))
  {
    i++;
  }
  /*  printf("compared  ");
  my_string_insertion(pLeft_string, stdout);
  printf("    and  ");
  my_string_insertion(pRight_string, stdout);
  printf("   sizes are = %d and %d    ", pLeft_string->size, pRight_string->size);
  */
if(i>=pLeft_string->size)
  {
    //printf("will return %d\n",0);
    return 0;
  }
//printf("will return %d\n",(int)pLeft_string->data[i] - (int)pRight_string->data[i]);
  return (int)pLeft_string->data[i] - (int)pRight_string->data[i];
}

//Assignment

void my_string_assignment(Item* pLeft, Item right)
{
  My_string* sLeft = (My_string*)*pLeft;
  My_string* sRight = (My_string*) right;
  int i;

  if(sLeft==NULL || sLeft->capacity < sRight->capacity)
  {
    if(sLeft!=NULL && sLeft->capacity < sRight->capacity)
    {
      my_string_destroy(pLeft);
    }
    sLeft = (My_string*) malloc(sizeof(My_string));
    if(sLeft==NULL)
    {
      printf("Failed to allocate memory for pLeft\n");
      return;
    }
    sLeft->data = (char*) malloc(sizeof(char)*sRight->capacity);
    if(sLeft->data==NULL)
    {
      free(sLeft);
      printf("Failed to allocate memory for pLeft->data\n");
      return;
    }
    sLeft->capacity = sRight->capacity;
  }

  for(i=0;i< sRight->size; i++)
  {
    sLeft->data[i] = sRight->data[i];
  }
  sLeft->size = sRight->size;
  *pLeft = sLeft;
}

//key_value
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
  My_string* cwf = (My_string*)current_word_family;
  My_string* nk = (My_string*)new_key;
  My_string* pWord = (My_string*)word;
  char* temp;
  int i;
  if(nk->capacity < cwf->capacity)
  {
    temp = (char*) malloc(sizeof(char)* cwf->capacity);
    if(temp == NULL)
    {
      printf("Failed to reallocate memory for new_key");
      return FAILURE;
    }
    nk->capacity = cwf->capacity;
    free(nk->data);
    nk->data = temp;
  }
  nk->size = pWord->size;
  for(i=0; i< nk->size; i++)
  {
    if(tolower(pWord->data[i]) == tolower(guess))
    {
      nk->data[i] = tolower(guess);
    }
    else
    {
      nk->data[i] = cwf->data[i];
    }
  }
  return SUCCESS;
}
Boolean is_same_key(MY_STRING word, MY_STRING hKey)
{
  My_string* w = word;
  My_string* pKey = hKey;
  int i;
  for(i = 0; i<w->size; i++)
  {
    if(pKey->data[i] != '-' && w->data[i] != pKey->data[i])
    {
      return FALSE;
    }
  }
  return TRUE;
}

Boolean my_string_contains_dash(MY_STRING pWord)
{
    My_string* w = (My_string*) pWord;
    int i;
    for(i = 0; i<w->size; i++)
    {
        if(w->data[i] == '-')
        {
            return TRUE;
        }
    }
    return FALSE;
}

Boolean my_string_contains(MY_STRING pWord, char c)
{
    My_string* w = (My_string*) pWord;
    int i;
    for(i = 0; i<w->size; i++)
    {
        if(tolower(w->data[i]) == tolower(c))
        {
            return TRUE;
        }
    }
    return FALSE;
}
//destroy
/*
void my_string_destroy(MY_STRING* phMy_string)
{
My_string* pMy_string = (My_string*)*phMy_string;
free(pMy_string->data);
free(pMy_string);
*phMy_string = NULL;
}
*/
void my_string_destroy(Item* pItem)
{
  My_string* pMy_string = (My_string*)*pItem;
  free(pMy_string->data);
  free(pMy_string);
  *pItem = NULL;
}
