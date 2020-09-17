
#include "my_string.h"
#include "status.h"
#include "generic.h"

typedef void* GENERIC_VECTOR;

GENERIC_VECTOR generic_vector_init_default(void);

int generic_vector_get_size(GENERIC_VECTOR hVector);
int generic_vector_get_capacity(GENERIC_VECTOR hVector);
Item* generic_vector_at(GENERIC_VECTOR hVector, int index);

Status generic_vector_push_back(GENERIC_VECTOR hVector, Item pItem);
Status generic_vector_pop_back(GENERIC_VECTOR hVector);

GENERIC_VECTOR generic_vector_copy_key(GENERIC_VECTOR hVector, MY_STRING hKey);

void generic_vector_print(GENERIC_VECTOR hVector);

void generic_vector_destroy(GENERIC_VECTOR* phVector);
