#ifndef __TEST_H__
#define __TEST_H__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "dlist.h"
#include "hashtable.h"

typedef size_t (*print3_func_t)(void *);
typedef size_t (*print_func_t)(dlistint_t *);
typedef size_t (*print2_func_t)(const hash_table_t *);

int valid_output_match(char *label, char *expected_output, print_func_t f, dlistint_t *param);
int valid_dlist_output_match(char *label, char *expected_output, print_func_t f, dlistint_t *param);
int valid_hashtable_output_match(char *label, char *expected_output, print2_func_t f, hash_table_t *param);

#endif
