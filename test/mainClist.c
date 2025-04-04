#include <check.h>
#include <stdlib.h>
#define LINKED_LIST_IMPLEMENTATION
#include "Circular_linked_List.h"

void print_int(int value) {
    printf("%d ", value);
}

START_TEST(test_list_create) {
    List_int* list = list_int_create();
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->tail);
    ck_assert_uint_eq(list->length, 0);
    list_int_destroy(list);
}
END_TEST

START_TEST(test_append_and_length) {
    List_int* list = list_int_create();
    
    ck_assert(list_int_append(list, 10));
    ck_assert_uint_eq(list_int_length(list), 1);
    
    ck_assert(list_int_append(list, 20));
    ck_assert_uint_eq(list_int_length(list), 2);
    
    list_int_destroy(list);
}
END_TEST

Suite* linked_list_suite(void) {
    Suite* s = suite_create("Circular Singly Linked List");
    TCase* tc_core = tcase_create("Core Functions");
    tcase_add_test(tc_core, test_list_create);
    tcase_add_test(tc_core, test_append_and_length);
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    SRunner* sr = srunner_create(linked_list_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}