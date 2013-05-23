/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Written by Alexander Whillas (z3446737) for COMP9021                              *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_list.c                                                       *
 *       quizz9.c                                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* THIS IS THE ONLY FILE YOU HAVE TO SUBMIT.
 * IT WILL BE COMPILED WITH THE OTHER FILES YOU HAVE BEEN PROVIDED WITH. */

#include "reorder.h"

void reorder(Node **const pt_to_pt_to_node) {
    Node *new_list = NULL;

    // Flip the array and take the head off it until reach the end.
    while(*pt_to_pt_to_node) {
        reverse_list(pt_to_pt_to_node);
        append_to_list((*pt_to_pt_to_node)->value, &new_list);
        remove_from_list((*pt_to_pt_to_node)->value, pt_to_pt_to_node);
    }
    
    free(*pt_to_pt_to_node);
    *pt_to_pt_to_node = new_list;
}

