#ifndef _MULTI_SET_DA_H
#define _MULTI_SET_DA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


typedef int elem_t;

typedef unsigned int pos_t;

typedef struct node_s *node_t;

typedef struct multi_set_s *multi_set;

typedef enum {
    ENULL = -1,
    ACTION_FAILURE = -2,
    ACTION_SUCCESS = 1
} action_status;


/* Create a new multi_set */
multi_set init(void);

/* Adds the specified element e to this set if it is not already present */
action_status add(multi_set m, const elem_t e);

/* Removes the specified element e from this set if it is present */
action_status rm(multi_set m, const elem_t e);

/* Get multi_set size */
size_t act_size(const multi_set m);
size_t max_size(const multi_set m);

/* Returns true if this set contains no elements */
bool is_empty(const multi_set m);

/* Returns true if this set contains the specified element e */
action_status contains(const multi_set m, const elem_t e);

/* Returns the first (lowest) element currently in this set */
elem_t first(const multi_set m);

/* Returns the last (highest) element currently in this set */
elem_t last(const multi_set m);

size_t count(const multi_set m, elem_t e);

action_status mts(multi_set m);

/* Empty the entire set */
action_status empty(multi_set m);

/* Write the elements of this set into stdout */
action_status dump(const multi_set m);

/* Free the dynamic memory used by the sorted_set */
action_status destroy(multi_set m);

#endif