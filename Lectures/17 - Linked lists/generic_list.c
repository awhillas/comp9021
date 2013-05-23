/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Defines list processing functions for generic lists whose      *
 *              nodes store values of type pointer to void.                    *
 *              This is meant to be complemented with an implementation of     *
 *              list processing functions for lists whose nodes store values   *
 *              of a given type, with one implementation for each such type.   *
 *              Those of the functions for generic lists that are not of type  *
 *              void *, that do not have an argument of type void *, and that  *
 *              do not have a pointer to a comparison function as an argument, *
 *              can be used as such and do not need to be complemented with an *
 *              implementation of corresponding functions for lists whose      *
 *              nodes store values of a specific type.                         *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "generic_list.h"

Node *create_node(void *const pt_to_value) {
    Node *const pt_to_node = malloc(sizeof(Node));
    assert(pt_to_node);
    pt_to_node->pt_to_value = pt_to_value;
    pt_to_node->pt_to_next_node = NULL;
    return pt_to_node;
}

Node *duplicate_list(const Node *pt_to_node) {
    if (!pt_to_node)
        return NULL;
    Node *const pt_to_node_copy = create_node(pt_to_node->pt_to_value);
    Node *pt_to_current_node = pt_to_node_copy;
    while (pt_to_node = pt_to_node->pt_to_next_node) {
        pt_to_current_node->pt_to_next_node = create_node(pt_to_node->pt_to_value);
        pt_to_current_node = pt_to_current_node->pt_to_next_node;
    }
    pt_to_current_node->pt_to_next_node = NULL;
    return pt_to_node_copy;
}

int list_length(const Node *pt_to_node) {
    int length = 0;
    while (pt_to_node) {
        pt_to_node = pt_to_node->pt_to_next_node;
        ++length;
    }
    return length;
}

void apply_to_list(void (*const function)(), const Node *pt_to_node) {
    while (pt_to_node) {
        function(pt_to_node->pt_to_value);
        pt_to_node = pt_to_node->pt_to_next_node;
    }
}

bool list_is_sorted(const Node *pt_to_node, int (*const cmp)()) {
    if (!pt_to_node)
        return true;
    while (pt_to_node->pt_to_next_node) {
        if (cmp(pt_to_node->pt_to_value, pt_to_node->pt_to_next_node->pt_to_value) > 0)
            return false;
        pt_to_node = pt_to_node->pt_to_next_node;
    }
    return true;
}
Node *append_list_to_list(Node *const pt_to_node_1, Node *const pt_to_node_2) {
    if (!pt_to_node_1)
        return pt_to_node_2;
    if (!pt_to_node_2)
        return pt_to_node_1;
    Node *pt_to_node = pt_to_node_1;
    while (pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_node_2;
    return pt_to_node_1;
}

void reverse_list(Node **const pt_to_pt_to_node) {
    if (!*pt_to_pt_to_node)
        return;
    Node *pt_to_last_node = NULL;
    Node *pt_to_node = *pt_to_pt_to_node;
    while (pt_to_node) {
        Node *pt_to_current_node = pt_to_node;
        pt_to_node = pt_to_node->pt_to_next_node;
        pt_to_current_node->pt_to_next_node = pt_to_last_node;
        pt_to_last_node = pt_to_current_node;
    }
    *pt_to_pt_to_node = pt_to_last_node;
}

int position_of_value_in_list(const void *const pt_to_value, Node *pt_to_node, int (*const cmp)()) {
    int position = 0;
    while (pt_to_node) {
        if (!cmp(pt_to_node->pt_to_value, pt_to_value))
            return position;
        ++position;
        pt_to_node = pt_to_node->pt_to_next_node;
    }
    return -1;
}

void *get_last_value_from_list(const Node *pt_to_node) {
    if (!pt_to_node)
        return NULL;
    while (pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    return pt_to_node->pt_to_value;
}

void *get_value_from_list_at(const Node *pt_to_node, int position) {
    if (position < 0)
        return NULL;
    while (position-- && pt_to_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    if (pt_to_node)
        return pt_to_node->pt_to_value;
    return NULL;
}

void prepend_to_list(void *const pt_to_value, Node **const pt_to_pt_to_node) {
    Node *pt_to_new_node = create_node(pt_to_value);
    pt_to_new_node->pt_to_next_node = *pt_to_pt_to_node;
    *pt_to_pt_to_node = pt_to_new_node;
}

void append_to_list(void *const pt_to_value, Node **const pt_to_pt_to_node) {
    Node *pt_to_new_node = create_node(pt_to_value);
    if (!*pt_to_pt_to_node) {
        *pt_to_pt_to_node = pt_to_new_node;
        return;
    }
    Node *pt_to_node = *pt_to_pt_to_node;
    while (pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
}

void insert_in_list_at(void *const pt_to_value, Node **const pt_to_pt_to_node, int position) {
    if (position <= 0) {
        prepend_to_list(pt_to_value, pt_to_pt_to_node);
        return;
    }
    Node *pt_to_new_node = create_node(pt_to_value);
    if (!*pt_to_pt_to_node) {
        *pt_to_pt_to_node = pt_to_new_node;
        return;
    }
    Node *pt_to_node = *pt_to_pt_to_node;
    while (--position && pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    pt_to_new_node->pt_to_next_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
}

bool insert_in_list_before(void *const pt_to_value_1, Node **const pt_to_pt_to_node, const void *const pt_to_value_2, int (*const cmp)()) {
    if (!*pt_to_pt_to_node)
        return false;
    if (!cmp((*pt_to_pt_to_node)->pt_to_value, pt_to_value_2)) {
        prepend_to_list(pt_to_value_1, pt_to_pt_to_node);
        return true;
    }
    Node *pt_to_node = *pt_to_pt_to_node;
    while (pt_to_node->pt_to_next_node && cmp(pt_to_node->pt_to_next_node->pt_to_value, pt_to_value_2))
        pt_to_node = pt_to_node->pt_to_next_node;
    if (!pt_to_node->pt_to_next_node)
        return false;
    Node *const pt_to_new_node = create_node(pt_to_value_1);
    pt_to_new_node->pt_to_next_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
    return true;
}
    
bool insert_in_list_after(void *const pt_to_value_1, Node *pt_to_node, const void *const pt_to_value_2, int (*const cmp)()) {
    if (!pt_to_node)
        return false;
    while (cmp(pt_to_node->pt_to_value, pt_to_value_2) && pt_to_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    if (cmp(pt_to_node->pt_to_value, pt_to_value_2))
        return false;
    Node *const pt_to_new_node = create_node(pt_to_value_1);
    pt_to_new_node->pt_to_next_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
    return true;
}

void insert_in_sorted_list(void *const pt_to_value, Node **const pt_to_pt_to_node, int (*const cmp)()) {
    Node *const pt_to_new_node = create_node(pt_to_value);
    if (!*pt_to_pt_to_node) {
        *pt_to_pt_to_node = pt_to_new_node;
        return;
    }
    Node *pt_to_node = *pt_to_pt_to_node;
    if (cmp(pt_to_node->pt_to_value, pt_to_value) >= 0) {
        pt_to_new_node->pt_to_next_node = pt_to_node;
        *pt_to_pt_to_node = pt_to_new_node;
        return;
    }
    while (pt_to_node->pt_to_next_node && cmp(pt_to_node->pt_to_next_node->pt_to_value, pt_to_value) < 0)
        pt_to_node = pt_to_node->pt_to_next_node;
    pt_to_new_node->pt_to_next_node = pt_to_node->pt_to_next_node;
    pt_to_node->pt_to_next_node = pt_to_new_node;
}

bool remove_from_list(void *pt_to_value, Node **const pt_to_pt_to_node, int (*const cmp)()) {
    if (!*pt_to_pt_to_node)
        return false;
    Node *pt_to_node = *pt_to_pt_to_node;
    if (!cmp(pt_to_node->pt_to_value, pt_to_value)) {
        *pt_to_pt_to_node = pt_to_node->pt_to_next_node;
        pt_to_value = pt_to_node->pt_to_value;
        free(pt_to_value);
        free(pt_to_node);
        return true;
    }
    if (!pt_to_node->pt_to_next_node)
        return false;
    while (cmp(pt_to_node->pt_to_next_node->pt_to_value, pt_to_value) && pt_to_node->pt_to_next_node->pt_to_next_node)
        pt_to_node = pt_to_node->pt_to_next_node;
    if (cmp(pt_to_node->pt_to_next_node->pt_to_value, pt_to_value))
        return false;
    Node *const pt_to_found_node = pt_to_node->pt_to_next_node;
    pt_to_value = pt_to_found_node->pt_to_value;
    pt_to_node->pt_to_next_node = pt_to_found_node->pt_to_next_node;
    free(pt_to_value);
    free(pt_to_found_node);
    return true;
}

void delete_list(Node **const pt_to_pt_to_node) {
    Node *pt_to_node = *pt_to_pt_to_node;
    while (pt_to_node) {
        Node *const pt_to_current_node = pt_to_node;
        void *const pt_to_value = pt_to_node->pt_to_value;
        pt_to_node = pt_to_node->pt_to_next_node;
        free(pt_to_value);
        free(pt_to_current_node);
    }
    *pt_to_pt_to_node = NULL;
}
