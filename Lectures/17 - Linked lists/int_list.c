/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Defines list processing functions for lists whose nodes        *
 *              store values of type pointer to int. This complements the      *
 *              implementation of list processing functions for generic list   *
 *              whose nodes store values of type pointer to void.              *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "int_list.h"

static int int_cmp(const int *const, const int *const );

static int int_cmp(const int *const i, const int *const j) {
    return *i - *j;
}

Node *create_int_node(const int value) {
    int *const pt_to_value = malloc(sizeof(int));
    *pt_to_value = value;
    return create_node(pt_to_value);
}

Node *duplicate_int_list(const Node *pt_to_node) {
    Node *pt_to_first_duplicated_node = duplicate_list(pt_to_node);
    Node *pt_to_current_node = pt_to_first_duplicated_node;
    while (pt_to_current_node) {
        int *pt_to_value = malloc(sizeof(int));
        *pt_to_value = *(int *)pt_to_current_node->pt_to_value;
        pt_to_current_node->pt_to_value = pt_to_value;
        pt_to_current_node = pt_to_current_node->pt_to_next_node;
    }
    return pt_to_first_duplicated_node;
}

bool int_list_is_sorted(const Node *const pt_to_node) {
    return list_is_sorted(pt_to_node, int_cmp);
}

int position_of_value_in_int_list(const int value, Node *const pt_to_node) {
    return position_of_value_in_list(&value, pt_to_node, int_cmp);
}

bool get_last_value_from_int_list(const Node *const pt_to_node, int *const pt_to_value) {
    int *pt_to_returned_value = get_last_value_from_list(pt_to_node);
    if (pt_to_returned_value)
        *pt_to_value = *pt_to_returned_value;
    return pt_to_returned_value;
}

bool get_value_from_int_list_at(const Node *pt_to_node, const int position, int *const pt_to_value) {
    int *pt_to_returned_value = get_value_from_list_at(pt_to_node, position);
    if (pt_to_returned_value)
        *pt_to_value = *pt_to_returned_value;
    return pt_to_returned_value;
}

void prepend_to_int_list(const int value, Node **const pt_to_pt_to_node) {
    int *pt_to_value = malloc(sizeof(int));
    *pt_to_value = value;
    prepend_to_list(pt_to_value, pt_to_pt_to_node);
}

void append_to_int_list(const int value, Node **const pt_to_pt_to_node) {
    int *pt_to_value = malloc(sizeof(int));
    *pt_to_value = value;
    append_to_list(pt_to_value, pt_to_pt_to_node);
}

void insert_in_int_list_at(const int value, Node **const pt_to_pt_to_node, const int position) {
    int *pt_to_value = malloc(sizeof(int));
    *pt_to_value = value;
    insert_in_list_at(pt_to_value, pt_to_pt_to_node, position);
}

bool insert_in_int_list_before(const int value_1, Node **const pt_to_pt_to_node, const int value_2) {
    int *pt_to_value = malloc(sizeof(int));
    *pt_to_value = value_1;
    return insert_in_list_before(pt_to_value, pt_to_pt_to_node, &value_2, int_cmp);
}

bool insert_in_int_list_after(const int value_1, Node *const pt_to_node, const int value_2) {
    int *pt_to_value = malloc(sizeof(int));
    *pt_to_value = value_1;
    return insert_in_list_after(pt_to_value, pt_to_node, &value_2, int_cmp);
}

void insert_in_sorted_int_list(const int value, Node **const pt_to_pt_to_node) {
    int *pt_to_value = malloc(sizeof(int));
    *pt_to_value = value;
    insert_in_sorted_list(pt_to_value, pt_to_pt_to_node, int_cmp);
}

bool remove_from_int_list(int value, Node **const pt_to_pt_to_node) {
    return remove_from_list(&value, pt_to_pt_to_node, int_cmp);
}    
