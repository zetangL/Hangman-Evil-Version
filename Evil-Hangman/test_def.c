#include <stdio.h>
#include "unit_test.h"

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
  MY_STRING hString = NULL;
  hString = my_string_init_default();
  if(hString == NULL)
  {
    my_string_destroy(&hString);
    strncpy(buffer, "test_init_default_returns_nonNULL\n"
    "my_string_init_default returns NULL", length);
    return FAILURE;
  }
  else
  {
    my_string_destroy(&hString);
    strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
    return SUCCESS;
  }
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_default();
  if(my_string_get_size(hString) != 0)
  {
    status = FAILURE;
    printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
    strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
    "Did not receive 0 from get_size after init_default\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
    , length);
  }
  my_string_destroy(&hString);
  return status;
}
//---------My test cases
Status test_zlei_get_capacity_on_init_default_returns_7(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_default();
  if(my_string_get_capacity(hString) != 7)
  {
    status = FAILURE;
    printf("Expected a capacity of 7 but got %d\n", my_string_get_capacity(hString));
    strncpy(buffer, "test_zlei_get_capacity_on_init_default_returns_7\n"
    "Did not receive 7 from get_capacity after init_default\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n"
    , length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_zlei_empty_on_init_default_return_TRUE(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_default();
  if(my_string_empty(hString) == FALSE)
  {
    status = FAILURE;
    printf("Expected TRUE but got FALSE");
    strncpy(buffer, "test_zlei_empty_on_init_default_return_TRUE\n"
    "Did not receive TRUE from string_empty after init_default\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_empty_on_init_default_return_TRUE\n"
    , length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_zlei_empty_on_init_c_string_return_FALSE(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_c_string("hi");
  if(my_string_empty(hString) == TRUE)
  {
    status = FAILURE;
    printf("Expected FALSE but got TRUE for test_zlei_empty_on_init_c_string_return_FALSE");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_empty_on_init_c_string_return_FALSE\n"
    , length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_zlei_get_size_on_init_c_string_return_nonZero(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_c_string("hi");
  if(my_string_get_size(hString)==0)
  {
    status = FAILURE;
    printf("Expected non 0 but got 0 for test_zlei_get_size_on_init_c_string_return_nonZero");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_get_size_on_init_c_string_return_nonZero\n"
    , length);
  }
  my_string_destroy(&hString);
  return status;
}
Status test_zlei_get_capacity_on_init_c_string_return_nonZero(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_c_string("hi");
  if(my_string_get_capacity(hString)==0)
  {
    status = FAILURE;
    printf("Expected non 0 but got 0 for test_zlei_get_capacity_on_init_c_string_return_nonZero");
    strncpy(buffer, "FAILURE", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_get_capacity_on_init_c_string_return_nonZero\n"
    , length);
  }
  my_string_destroy(&hString);
  return status;
}
Status test_zlei_pop_back_on_init_default_return_FAILURE(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_default();
  if(my_string_pop_back(hString)==SUCCESS)
  {
    status = FAILURE;
    printf("Expected FAILURE but got SUCCESS for test_zlei_pop_back_on_init_default_return_FAILURE");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_pop_back_on_init_default_return_FAILURE\n"
    , length);
  }
  my_string_destroy(&hString);
  return status;

}
Status test_zlei_push_back_on_init_default_return_SUCCESS(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_default();
  if(my_string_push_back(hString, 'c')==FAILURE)
  {
    status = FAILURE;
    printf("Expected SUCCESS but got FAILURE for test_zlei_push_back_on_init_default_return_SUCCESS");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_push_back_on_init_default_return_SUCCESS\n"
    , length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_zlei_pop_back_on_init_c_string_return_SUCCESS(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_c_string("hi");
  if(my_string_pop_back(hString)==FAILURE)
  {
    status = FAILURE;
    printf("Expected SUCCESS but got FAILURE for test_zlei_pop_back_on_init_c_string_return_SUCCESS");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_pop_back_on_init_c_string_return_SUCCESS\n"
    , length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_zlei_push_back_on_init_c_string_return_SUCCESS(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_c_string("hi");
  if(my_string_push_back(hString,'c')==FAILURE)
  {
    status = FAILURE;
    printf("Expected SUCCESS but got FAILURE for test_zlei_push_back_on_init_c_string_return_SUCCESS");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_push_back_on_init_c_string_return_SUCCESS\n"
    , length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_zlei_compare_on_same_init_default_return_0(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  int i;
  hString = my_string_init_default();
  if(my_string_compare(hString, hString)!=0)
  {
    status = FAILURE;
    i = my_string_compare(hString, hString);
    printf("Expected 0 but got %d for test_zlei_compare_on_same_init_default_return_0", i);
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_compare_on_same_init_default_return_0\n"
    , length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_zlei_compare_on_different_init_c_string_return_nonZero(char* buffer, int length)
{
  MY_STRING hString = NULL;
  MY_STRING hStr2 = NULL;
  Status status;
  hString = my_string_init_c_string("hi");
  hStr2 = my_string_init_c_string("hello");
  if(my_string_compare(hString,hStr2)==0)
  {
    status = FAILURE;
    printf("Expected non Zero but got 0 for test_zlei_compare_on_different_init_c_string_return_nonZero");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_compare_on_different_init_c_string_return_nonZero\n"
    , length);
  }
  my_string_destroy(&hString);
  my_string_destroy(&hStr2);
  return status;
}

Status test_zlei_concat_on_two_init_default_return_SUCCESS(char* buffer, int length)
{
  MY_STRING hString = NULL;
  MY_STRING hStr2 = NULL;
  Status status;
  hString = my_string_init_default();
  hStr2 = my_string_init_default();
  if(my_string_concat(hString, hStr2)==FAILURE)
  {
    status = FAILURE;
    printf("Expected SUCCESS but got FAILURE for test_zlei_concat_on_two_init_default_return_SUCCESS");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_concat_on_two_init_default_return_SUCCESS\n"
    , length);
  }
  my_string_destroy(&hString);
  my_string_destroy(&hStr2);
  return status;
}

Status test_zlei_empty_on_concat_two_init_default_return_TRUE(char* buffer, int length)
{
  MY_STRING hString = NULL;
  MY_STRING hStr2 = NULL;
  Status status;
  hString = my_string_init_default();
  hStr2 = my_string_init_default();
  my_string_concat(hString, hStr2);
  if(my_string_empty(hString)==FALSE)
  {
    status = FAILURE;
    printf("Expected TRUE but got FALSE for test_zlei_empty_on_concat_two_init_default_return_TRUE");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_empty_on_concat_two_init_default_return_TRUE\n"
    , length);
  }
  my_string_destroy(&hString);
  my_string_destroy(&hStr2);
  return status;
}

Status test_zlei_concat_on_1_init_default_1_c_string_return_SUCCESS(char* buffer, int length)
{
  MY_STRING hString = NULL;
  MY_STRING hStr2 = NULL;
  Status status;
  hString = my_string_init_default();
  hStr2 = my_string_init_c_string("hello");
  if(my_string_concat(hString,hStr2)==FAILURE)
  {
    status = FAILURE;
    printf("Expected SUCCESS but got FAILURE for test_zlei_concat_on_1_init_default_1_c_string_return_SUCCESS");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_concat_on_1_init_default_1_c_string_return_SUCCESS\n"
    , length);
  }
  my_string_destroy(&hString);
  my_string_destroy(&hStr2);
  return status;
}

Status test_zlei_empty_on_1_default_1_c_string_return_FALSE(char* buffer, int length)
{
  MY_STRING hString = NULL;
  MY_STRING hStr2 = NULL;
  Status status;
  hString = my_string_init_default();
  hStr2 = my_string_init_c_string("hello");
  my_string_concat(hString, hStr2);
  if(my_string_empty(hString)==TRUE)
  {
    status = FAILURE;
    printf("Expected FALSE but got TRUE for test_zlei_empty_on_1_default_1_c_string_return_FALSE");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_empty_on_1_default_1_c_string_return_FALSE\n"
    , length);
  }
  my_string_destroy(&hString);
  my_string_destroy(&hStr2);
  return status;
}

Status test_zlei_concat_on_2_nonempty_c_string_return_SUCCESS(char* buffer, int length)
{
  MY_STRING hString = NULL;
  MY_STRING hStr2 = NULL;
  Status status;
  hString = my_string_init_c_string("hi");
  hStr2 = my_string_init_c_string("hello");
  if(my_string_concat(hString, hStr2)==FAILURE)
  {
    status = FAILURE;
    printf("Expected SUCCESS but got FAILURE for test_zlei_concat_on_2_nonempty_c_string_return_SUCCESS");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_concat_on_2_nonempty_c_string_return_SUCCESS\n"
    , length);
  }
  my_string_destroy(&hString);
  my_string_destroy(&hStr2);
  return status;
}

Status test_zlei_empty_on_concat_2_nonempty_c_string_return_FALSE(char* buffer, int length)
{
  MY_STRING hString = NULL;
  MY_STRING hStr2 = NULL;
  Status status;
  hString = my_string_init_c_string("hi");
  hStr2 = my_string_init_c_string("hello");
  my_string_concat(hString, hStr2);
  if(my_string_empty(hString)==TRUE)
  {
    status = FAILURE;
    printf("Expected FALSE but got TRUE for test_zlei_empty_on_concat_2_nonempty_c_string_return_FALSE");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_empty_on_concat_2_nonempty_c_string_return_FALSE\n"
    , length);
  }
  my_string_destroy(&hString);
  my_string_destroy(&hStr2);
  return status;
}

Status test_zlei_string_at_on_init_default_return_NULL(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_default();
  if(my_string_at(hString,0)!=NULL)
  {
    status = FAILURE;
    printf("Expected NULL but got non NULL for test_zlei_string_at_on_init_default_return_NULL");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_string_at_on_init_default_return_NULL\n"
    , length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_zlei_string_at_inbound_on_init_c_string_return_nonNull(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_c_string("hi");
  if(my_string_at(hString,0)==NULL)
  {
    status = FAILURE;
    printf("Expected non NULL but got NULL for test_zlei_string_at_inbound_on_init_c_string_return_nonNull");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_string_at_inbound_on_init_c_string_return_nonNull\n"
    , length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_zlei_string_at_outbount_on_init_c_string_return_NULL(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_c_string("hi");
  if(my_string_at(hString,100)!=NULL)
  {
    status = FAILURE;
    printf("Expected NULL but got non NULL for test_zlei_string_at_outbount_on_init_c_string_return_NULL");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_string_at_outbount_on_init_c_string_return_NULL\n"
    , length);
  }
  my_string_destroy(&hString);
  return status;

}
Status test_zlei_pop_back_on_concat_2_init_default_return_FAILURE(char* buffer, int length)
{
  MY_STRING hString = NULL;
  MY_STRING hStr2 = NULL;
  Status status;
  hString = my_string_init_default();
  hStr2 = my_string_init_default();
  my_string_concat(hString, hStr2);
  if(my_string_pop_back(hString)==SUCCESS)
  {
    status = FAILURE;
    printf("Expected FAILURE but got SUCCESS for test_zlei_pop_back_on_concat_2_init_default_return_FAILURE");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_pop_back_on_concat_2_init_default_return_FAILURE\n", length);
  }
  my_string_destroy(&hString);
  my_string_destroy(&hStr2);
  return status;
}

Status test_zlei_pop_back_on_concat_1_default_1_c_string_return_SUCCESS(char* buffer, int length)
{
  MY_STRING hString = NULL;
  MY_STRING hStr2 = NULL;
  Status status;  
  hString = my_string_init_default();
  hStr2 = my_string_init_c_string("hello");
  my_string_concat(hString, hStr2);
  if(my_string_pop_back(hString) == FAILURE)
  {
    status = FAILURE;
    printf("Expected SUCCESS but got FAILURE for test_zlei_pop_back_on_concat_1_default_1_c_string_return_SUCCESS");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_pop_back_on_concat_1_default_1_c_string_return_SUCCESS\n"
    , length);
  }
  my_string_destroy(&hString);
  my_string_destroy(&hStr2);
  return status;
}

Status test_zlei_pop_back_on_concat_2_nonempty_c_string_return_SUCCESS(char* buffer, int length)
{
  MY_STRING hString = NULL;
  MY_STRING hStr2 = NULL;
  Status status;  
  hString = my_string_init_c_string("hi");
  hStr2 = my_string_init_c_string("hello");
  my_string_concat(hString, hStr2);
  if(my_string_pop_back(hString)==FAILURE)
  {
    status = FAILURE;
    printf("Expected SUCCESS but got FAILURE for test_zlei_pop_back_on_concat_2_nonempty_c_string_return_SUCCESS");
    strncpy(buffer, " ", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_zlei_pop_back_on_concat_2_nonempty_c_string_return_SUCCESS\n"
    , length);
  }
  my_string_destroy(&hString);
  my_string_destroy(&hStr2);
  return status;
}

