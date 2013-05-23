#ifndef _GENERIC_LIST_H_
#define _GENERIC_LIST_H_

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

/* The pt_to_value field is a generic pointer to a value whose type can be arbitrary;
 * we use the expression "datum address" to refer to this field. */
typedef struct node {
    void *pt_to_value;
    struct node *pt_to_next_node;
} Node;

/* Returns the address of a newly created node that stores pt_to_value.
 * The value of the datum address of the node is assumed to be allocated on the heap
 * by a corresponding function that deals with values of a specific type; this is
 * necessary as the functions remove_from_list() and delete_list() deallocate
 * memory for both the nodes themselves and the values of their data addresses. */
Node *create_node(void *const pt_to_value);

/* Returns the address of the first node of a new list that is the clone of the list
 * that starts at pt_to_node.
 * The data addresses in both lists are the same.
 * A corresponding function for values of a specific type should allocate memory and
 * make them different as the functions remove_from_list() and delete_list() deallocate
 * memory for both the nodes themselves and the values of their data addresses. */
Node *duplicate_list(const Node *pt_to_node);

/* Returns the length of the list that starts at pt_to_node. */
int list_length(const Node *pt_to_node);

/* Applies the function which is the value of pt_to_function to the values stored
 * at all data addresses in the list that starts at pt_to_node. */
void apply_to_list(void (*const pt_to_function)(), const Node *pt_to_node);

/* Returns true or false, depending on whether or not the list that starts
 * at pt_to_node is sorted.
 * pt_to_cmp is a pointer to the comparison function. */
bool list_is_sorted(const Node *pt_to_node, int (*const pt_to_cmp)());

/* Concatenates the lists that start at pt_to_node_1 and pt_to_node_2, respectively.
 * If the first list is not empty then pt_to_node_1 becomes the address of the first node
 * of the concatenated list; otherwise pt_to_node_2 becomes the address of the first node
 * of the concatenated list. */
Node *append_list_to_list(Node *const pt_to_node_1, Node *const pt_to_node_2);

/* Reverses the list that starts at the value of pt_to_pt_to_node and updates the
 * value of pt_to_pt_to_node to the address of the first node of the resulting list
 * (that is, the last node of the original list). */
void reverse_list(Node **const pt_to_pt_to_node);

/* If the value stored at pt_to_value is identical to one of the values stored at
 * the data addresses of the list that starts at pt_to_node, then returns the index
 * (indexing the nodes from 0) of the first node that has such a datum address;
 * otherwise returns -1.
 * pt_to_cmp is a pointer to the comparison function. */
int position_of_value_in_list(const void *const pt_to_value, Node *pt_to_node, int (*const pt_to_cmp)());

/* Returns the datum address of the last node of the list that starts at pt_to_node,
 * and NULL if that list is empty. */
void *get_last_value_from_list(const Node *pt_to_node);

/* Returns the datum address of the n-th node of the list that starts at pt_to_node
 * (indexing the nodes from 0).
 * Returns NULL if n is not between 0 and the length of the list minus 1. */
void *get_value_from_list_at(const Node *pt_to_node, int n);

/* Adds at the beginning of the list that starts at the value of pt_to_pt_to_node,
 * a node whose datum address is a location where a value equal to the value stored
 * at pt_to_value is stored, and updates the value of pt_to_pt_to_node to the address
 * of the first node of the resulting list. */
void prepend_to_list(void *const pt_to_value, Node **const pt_to_pt_to_node);

/* Adds at the end of the list that starts at the value of pt_to_pt_to_node,
 * a node whose datum address is a location where a value equal to the value stored
 * at pt_to_value is stored, and updates the value of pt_to_pt_to_node to the address
 * of the first node of the resulting list. */
void append_to_list(void *const pt_to_value, Node **const pt_to_pt_to_node);

/* Inserts at index n (indexing the nodes from 0) in the list that starts at the value
 * of pt_to_pt_to_node, a node whose datum address is a location where a value equal to
 * the value stored at pt_to_value is stored, and updates the value of pt_to_pt_to_node
 * to the address of the first node of the resulting list.
 * If the index is smaller than 0 then the node is inserted at the beginning.
 * If the index is at least equal to the length of the original list
 * then the node is inserted at the end. */
void insert_in_list_at(void *const pt_to_value, Node **const pt_to_pt_to_node, int n);

/* Inserts in the list that starts at the value of pt_to_pt_to_node, before
 * the first node whose datum address is a location where a value equal to the value
 * stored at pt_to_value_2 is stored, a node whose datum address is a location
 * where a value equal to the value stored at pt_to_value_1 is stored, and updates the
 * value of pt_to_pt_to_node to the address of the first node of the resulting list.
 * If the value stored at pt_to_value_2 is not stored in the list then the list
 * is unchanged and the function returns false; otherwise the function returns true.
 * pt_to_cmp is the address of the comparison function. */
bool insert_in_list_before(void *const pt_to_value_1, Node **const pt_to_pt_to_node, const void *const pt_to_value_2, int (*const pt_to_cmp)());

/* Inserts in the list that starts at pt_to_node, after the first node whose datum address
 * is a location where a value equal to the value stored at pt_to_value_2 is stored,
 * a node whose datum address is a location where a value equal to the value stored
 * at pt_to_value_1 is stored.
 * If the value stored at pt_to_value_2 is not stored in the list then the list
 * is unchanged and the function returns false; otherwise the function returns true.
 * pt_to_cmp is the address of the comparison function. */
 bool insert_in_list_after(void *const pt_to_value_1, Node *pt_to_node, const void *const pt_to_value_2, int (*const pt_to_cmp)());

/* Inserts in the list that starts at the value of pt_to_pt_to_node, and that is
 * assumed to be sorted, a node whose datum address is a location where a value equal
 * to the value stored at pt_to_value is stored, so that the resulting list remains
 * sorted, and updates the value of pt_to_pt_to_node to the address of the first node
 * of the resulting list.
 * pt_to_cmp is the address of the comparison function. */
void insert_in_sorted_list(void *const pt_to_value, Node **const pt_to_pt_to_node, int (*const pt_to_cmp)());

/* Removes in the list that starts at the value of pt_to_pt_to_node, the first node
 * whose datum address is a location where a value equal to the value stored at
 * pt_to_value is stored, and updates the value of pt_to_pt_to_node to the address
 * of the first node of the resulting list.
 * If the value stored at pt_to_value is not stored in the list then the list
 * is unchanged and the function returns false; otherwise the function returns true.
 * pt_to_cmp is the address of the comparison function. */
bool remove_from_list(void *pt_to_value, Node **const pt_to_pt_to_node, int (*const pt_to_cmp)());

/* Deletes all nodes of the list that starts at the value of pt_to_pt_to_node,
 * and sets that value to NULL. */
void delete_list(Node **const pt_to_pt_to_node);

#endif
