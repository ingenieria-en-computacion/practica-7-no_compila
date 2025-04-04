#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// ----------------------------
// Macro para declarar estructuras y prototipos
// ----------------------------
#define DECLARE_CIRCULAR_LINKED_LIST(TYPE) \
    typedef struct Node_##TYPE { \
        TYPE data; \
        struct Node_##TYPE* next; \
    } Node_##TYPE; \
    \
    typedef struct { \
        Node_##TYPE* tail; \
        size_t length; \
    } List_##TYPE; \
    \
    List_##TYPE* list_##TYPE##_create(void); \
    void list_##TYPE##_destroy(List_##TYPE* list); \
    bool list_##TYPE##_insert(List_##TYPE* list, TYPE data, size_t pos); \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data); \
    bool list_##TYPE##_remove_at(List_##TYPE* list, size_t pos); \
    bool list_##TYPE##_get(const List_##TYPE* list, size_t pos, TYPE* out); \
    size_t list_##TYPE##_length(const List_##TYPE* list); \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE));

// ----------------------------
// Macro para implementación
// ----------------------------
#define IMPLEMENT_CIRCULAR_LINKED_LIST(TYPE) \
    List_##TYPE* list_##TYPE##_create(void) { \
        List_##TYPE* list = malloc(sizeof(List_##TYPE)); \
        if (!list) return NULL; \
        list->tail = NULL; \
        list->length = 0; \
        return list; \
    } \
    \
    void list_##TYPE##_destroy(List_##TYPE* list) { \
        if (!list || !list->tail) return; \
        Node_##TYPE* current = list->tail->next; \
        for (size_t i = 0; i < list->length; i++) { \
            Node_##TYPE* temp = current; \
            current = current->next; \
            free(temp); \
        } \
        free(list); \
    } \
    \
    bool list_##TYPE##_insert(List_##TYPE* list, TYPE data, size_t pos) { \
        if (!list || pos > list->length) return false; \
        Node_##TYPE* new_node = malloc(sizeof(Node_##TYPE)); \
        if (!new_node) return false; \
        new_node->data = data; \
        \
        if (list->length == 0) { \
            new_node->next = new_node; \
            list->tail = new_node; \
        } else { \
            Node_##TYPE* temp = list->tail->next; \
            for (size_t i = 0; i < pos - 1; i++) temp = temp->next; \
            new_node->next = temp->next; \
            temp->next = new_node; \
            if (pos == 0) list->tail->next = new_node; \
            if (pos == list->length) list->tail = new_node; \
        } \
        list->length++; \
        return true; \
    } \
    \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data) { \
        return list_##TYPE##_insert(list, data, list->length); \
    } \
    \
    bool list_##TYPE##_remove_at(List_##TYPE* list, size_t pos) { \
        if (!list || list->length == 0 || pos >= list->length) return false; \
        Node_##TYPE* temp = list->tail->next; \
        Node_##TYPE* prev = list->tail; \
        for (size_t i = 0; i < pos; i++) { \
            prev = temp; \
            temp = temp->next; \
        } \
        prev->next = temp->next; \
        if (pos == 0) list->tail->next = temp->next; \
        if (temp == list->tail) list->tail = prev; \
        free(temp); \
        list->length--; \
        return true; \
    } \
    \
    bool list_##TYPE##_get(const List_##TYPE* list, size_t pos, TYPE* out) { \
        if (!list || !out || pos >= list->length) return false; \
        Node_##TYPE* temp = list->tail->next; \
        for (size_t i = 0; i < pos; i++) temp = temp->next; \
        *out = temp->data; \
        return true; \
    } \
    \
    size_t list_##TYPE##_length(const List_##TYPE* list) { \
        return list ? list->length : 0; \
    } \
    \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE)) { \
        if (!list || !print_fn || list->length == 0) return; \
        Node_##TYPE* current = list->tail->next; \
        for (size_t i = 0; i < list->length; i++) { \
            print_fn(current->data); \
            if (i < list->length - 1) printf(", "); \
            current = current->next; \
        } \
        printf("\n"); \
    }

// ----------------------------
// Declaración para tipos concretos
// ----------------------------
DECLARE_CIRCULAR_LINKED_LIST(int)
DECLARE_CIRCULAR_LINKED_LIST(char)
DECLARE_CIRCULAR_LINKED_LIST(float)

// ----------------------------
// Implementación para tipos concretos
// ----------------------------
#ifdef LINKED_LIST_IMPLEMENTATION
IMPLEMENT_CIRCULAR_LINKED_LIST(int)
IMPLEMENT_CIRCULAR_LINKED_LIST(char)
IMPLEMENT_CIRCULAR_LINKED_LIST(float)
#endif
