#include <stdio.h>
#include "unit_test.h"
int main(int argc, char* argv[])
{
  Status (*tests[])(char*, int) =
    {
      test_init_default_returns_nonNULL,
      test_get_size_on_init_default_returns_0,
      test_zlei_get_capacity_on_init_default_returns_7,
      test_zlei_empty_on_init_default_return_TRUE,
      test_zlei_empty_on_init_c_string_return_FALSE,
      
      test_zlei_get_size_on_init_c_string_return_nonZero,
      test_zlei_get_capacity_on_init_c_string_return_nonZero,
      test_zlei_pop_back_on_init_default_return_FAILURE,
      test_zlei_push_back_on_init_default_return_SUCCESS,
      test_zlei_pop_back_on_init_c_string_return_SUCCESS,
      test_zlei_push_back_on_init_c_string_return_SUCCESS,
      test_zlei_compare_on_same_init_default_return_0,
      test_zlei_compare_on_different_init_c_string_return_nonZero,
      test_zlei_concat_on_two_init_default_return_SUCCESS,
      test_zlei_empty_on_concat_two_init_default_return_TRUE,
      test_zlei_concat_on_1_init_default_1_c_string_return_SUCCESS,
      test_zlei_empty_on_1_default_1_c_string_return_FALSE,
      test_zlei_concat_on_2_nonempty_c_string_return_SUCCESS,
      test_zlei_empty_on_concat_2_nonempty_c_string_return_FALSE,
      test_zlei_string_at_on_init_default_return_NULL,
      test_zlei_string_at_inbound_on_init_c_string_return_nonNull,
      test_zlei_string_at_outbount_on_init_c_string_return_NULL,
      test_zlei_pop_back_on_concat_2_init_default_return_FAILURE,
      test_zlei_pop_back_on_concat_1_default_1_c_string_return_SUCCESS,
      test_zlei_pop_back_on_concat_2_nonempty_c_string_return_SUCCESS
    };
  int number_of_functions = sizeof(tests) / sizeof(tests[0]);
  int i;
  char buffer[500];
  int success_count = 0;
  int failure_count = 0;
  for(i=0; i<number_of_functions; i++)
    {
      if(tests[i](buffer, 500) == FAILURE)
	{
	  printf("FAILED: Test %d failed miserably\n", i);
	  printf("\t%s\n", buffer);
	  failure_count++;
	}
      else
	{
	  // printf("PASS: Test %d passed\n", i);
	  // printf("\t%s\n", buffer);
	  success_count++;
	}
    }
  printf("Total number of tests: %d\n", number_of_functions);
  printf("%d/%d Pass, %d/%d Failure\n", success_count,
	 number_of_functions, failure_count, number_of_functions);
  return 0;
}
