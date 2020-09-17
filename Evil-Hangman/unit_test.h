#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"
#include <string.h>

Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);

//My cases
Status test_zlei_get_capacity_on_init_default_returns_7(char* buffer, int length);
Status test_zlei_empty_on_init_default_return_TRUE(char* buffer, int length);
Status test_zlei_empty_on_init_c_string_return_FALSE(char* buffer, int length);

Status test_zlei_get_size_on_init_c_string_return_nonZero(char* buffer, int length);
Status test_zlei_get_capacity_on_init_c_string_return_nonZero(char* buffer, int length);
Status test_zlei_pop_back_on_init_default_return_FAILURE(char* buffer, int length);
Status test_zlei_push_back_on_init_default_return_SUCCESS(char* buffer, int length);
Status test_zlei_pop_back_on_init_c_string_return_SUCCESS(char* buffer, int length);
Status test_zlei_push_back_on_init_c_string_return_SUCCESS(char* buffer, int length);
Status test_zlei_compare_on_same_init_default_return_0(char* buffer, int length);
Status test_zlei_compare_on_different_init_c_string_return_nonZero(char* buffer, int length);
Status test_zlei_concat_on_two_init_default_return_SUCCESS(char* buffer, int length);
Status test_zlei_empty_on_concat_two_init_default_return_TRUE(char* buffer, int length);
Status test_zlei_concat_on_1_init_default_1_c_string_return_SUCCESS(char* buffer, int length);
Status test_zlei_empty_on_1_default_1_c_string_return_FALSE(char* buffer, int length);
Status test_zlei_concat_on_2_nonempty_c_string_return_SUCCESS(char* buffer, int length);
Status test_zlei_empty_on_concat_2_nonempty_c_string_return_FALSE(char* buffer, int length);
Status test_zlei_string_at_on_init_default_return_NULL(char* buffer, int length);
Status test_zlei_string_at_inbound_on_init_c_string_return_nonNull(char* buffer, int length);
Status test_zlei_string_at_outbount_on_init_c_string_return_NULL(char* buffer, int length);
Status test_zlei_pop_back_on_concat_2_init_default_return_FAILURE(char* buffer, int length);
Status test_zlei_pop_back_on_concat_1_default_1_c_string_return_SUCCESS(char* buffer, int length);
Status test_zlei_pop_back_on_concat_2_nonempty_c_string_return_SUCCESS(char* buffer, int length);

#endif
