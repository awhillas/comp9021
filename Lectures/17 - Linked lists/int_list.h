#ifndef _INT_LIST_H_
#define _INT_LIST_H_

#include "generic_list.h"

/* By "list of ints" we mean a list the values of whose data addresses are ints. */

/* Returns the address of a newly created node that stores an address where val is stored.
 * Memory is allocated on the heap to store val. */
Node *create_int_node(const int val);

/* Returns the address of the first node of a new list of ints that is the clone of the list
 * that starts at pt_to_node.
 * The data addresses in both lists are different; memory is allocated on the heap to store
 * the values of the data addresses of the cloned list. */
Node *duplicate_int_list(const Node *pt_to_node);

/* Returns true or false, depending on whether or not the list of ints that starts
 * at pt_to_node is sorted. */
bool int_list_is_sorted(const Node *const pt_to_node);

/* If val is identical to one of the values stored in the list of ints that starts
 * at pt_to_node, then returns the index (indexing the nodes from 0) of the first node
 * that indirectly stores val; otherwise returns -1. */
int position_of_value_in_int_list(const int val, Node *const pt_to_node);

/* If the list of ints that starts at pt_to_node is empty then returns false;
 * otherwise, returns true and sets the value stored at pt_to_value to the value
 * that is indirectly stored in the last node of the list. */
bool get_last_value_from_int_list(const Node *const pt_to_node, int *const pt_to_value);

/* Returns false if n is not at least equal to 0 and strictly smaller than the length
 * of the list of ints that starts at pt_to_node; otherwise, returns true and sets
 * the value stored at pt_to_value to the value that is indirectly stored in the n-th
 * node of the list (indexing the nodes from 0). */
bool get_value_from_int_list_at(const Node *const pt_to_node, const int n, int *const pt_to_value);

/* Adds at the beginning of the list of ints that starts at the value of pt_to_pt_to_node,
 * a node that indirectly stores val, and updates the value of pt_to_pt_to_node to
 * the address of the first node of the resulting list. */
void prepend_to_int_list(const int val, Node **const pt_to_pt_to_node);

/* Adds at the end of the list of ints that starts at the value of pt_to_pt_to_node,
 * a node that indirectly stores val, and updates the value of pt_to_pt_to_node
 * to the address of the first node of the resulting list. */
void append_to_int_list(const int val, Node **pt_to_pt_to_node);

/* Inserts at index n (indexing the nodes from 0) in the list of ints that starts at the value
 * of pt_to_pt_to_node, a node that indirectly stores val, and updates the value of
 * pt_to_pt_to_node to the address of the first node of the resulting list.
 * If the index is smaller than 0 then the node is inserted at the beginning.
 * If the index is at least equal to the length of the original list
 * then the node is inserted at the end. */
void insert_in_int_list_at(const int val, Node **const pt_to_pt_to_node, const int n);

/* Inserts in the list of ints that starts at the value of pt_to_pt_to_node, before
 * the first node that stores val_2, a node that indirectly stores val_1,
 * and updates the value of pt_to_pt_to_node to the address of the first node of the
 * resulting list.
 * If val_2 is not stored in the list then the list is unchanged and the function
 * returns false; otherwise the function returns true. */
bool insert_in_int_list_before(const int val_1, Node **const pt_to_pt_to_node, const int val_2);
    
/* Inserts in the list of ints that starts at pt_to_node, after the first node
 * that stores val_2, a node that indirectly stores val_1.
 * If val_2 is not stored in the list then the list is unchanged and the function
 * returns false; otherwise the function returns true. */
bool insert_in_int_list_after(const int val_1, Node *const pt_to_node, const int val_2);

/* Inserts in the list of ints that starts at the value of pt_to_pt_to_node, and that is
 * assumed to be sorted, a node that indirectly stores val so that the resulting list
 * remains sorted, and updates the value of pt_to_pt_to_node to the address of the first node
 * of the resulting list. */
void insert_in_sorted_int_list(const int val, Node **const pt_to_pt_to_node);

/* Removes in the list of ints that starts at the value of pt_to_pt_to_node, the first node
 * that indirectly stores val, and updates the value of pt_to_pt_to_node to the address
 * of the first node of the resulting list.
 * If val is not stored in the list then the list is unchanged and the function
 * returns false; otherwise the function returns true. */
bool remove_from_int_list(int val, Node **const pt_to_pt_to_node);

#endif
