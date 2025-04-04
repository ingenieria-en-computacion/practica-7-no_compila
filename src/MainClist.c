#include <check.h>
#include <stdlib.h>
#define LINKED_LIST_IMPLEMENTATION
#include "Circular_linked_List.h"

// Función auxiliar para imprimir enteros
void print_int(int value) {
    printf("%d", value);
}

// Función auxiliar para imprimir caracteres
void print_char(char value) {
    printf("%c", value);
}

/* ----------------------------- */
/*      Pruebas para enteros     */
/* ----------------------------- */

START_TEST(test_list_int_create) {
    List_int* nums = list_int_create();
    ck_assert_ptr_nonnull(nums);
    ck_assert_ptr_null(nums->tail);
    ck_assert_uint_eq(nums->length, 0);
    list_int_destroy(nums);
}
END_TEST

START_TEST(test_list_int_append) {
    List_int* nums = list_int_create();
    ck_assert(list_int_append(nums, 10));
    ck_assert(list_int_append(nums, 20));
    ck_assert_uint_eq(list_int_length(nums), 2);
    
    int value;
    ck_assert(list_int_get(nums, 0, &value));
    ck_assert_int_eq(value, 10);
    
    ck_assert(list_int_get(nums, 1, &value));
    ck_assert_int_eq(value, 20);

    list_int_destroy(nums);
}
END_TEST

/* ----------------------------- */
/*     Pruebas para caracteres   */
/* ----------------------------- */

START_TEST(test_list_char_create) {
    List_char* chars = list_char_create();
    ck_assert_ptr_nonnull(chars);
    ck_assert_ptr_null(chars->tail);
    ck_assert_uint_eq(chars->length, 0);
    list_char_destroy(chars);
}
END_TEST

START_TEST(test_list_char_append) {
    List_char* chars = list_char_create();
    ck_assert(list_char_append(chars, 'a'));
    ck_assert(list_char_append(chars, 'b'));
    ck_assert(list_char_append(chars, 'c'));
    ck_assert(list_char_append(chars, 'd'));
    ck_assert(list_char_append(chars, 'e'));

    ck_assert_uint_eq(list_char_length(chars), 5);

    char value;
    ck_assert(list_char_get(chars, 0, &value));
    ck_assert_int_eq(value, 'a');

    ck_assert(list_char_get(chars, 4, &value));
    ck_assert_int_eq(value, 'e');

    list_char_destroy(chars);
}
END_TEST

/* ----------------------------- */
/*      Creación de la suite     */
/* ----------------------------- */

Suite* linked_list_suite(void) {
    Suite* s = suite_create("Circular Linked List");

    TCase* tc_int = tcase_create("Integer List");
    tcase_add_test(tc_int, test_list_int_create);
    tcase_add_test(tc_int, test_list_int_append);
    
    TCase* tc_char = tcase_create("Character List");
    tcase_add_test(tc_char, test_list_char_create);
    tcase_add_test(tc_char, test_list_char_append);
    
    suite_add_tcase(s, tc_int);
    suite_add_tcase(s, tc_char);
    
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