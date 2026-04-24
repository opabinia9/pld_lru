#ifndef __TEST_H__
#define __TEST_H__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "dlist.h"
#include "hashtable.h"
#include "lru.h"

typedef void (*print_func_t)(void *);
typedef void (*print_func_t2)(dliststr_t *);
typedef void (*print_func_t3)(const hash_table_t *);
typedef void (*print_func_t4)(lru_t *);

int valid_dlist_output_match(char *label, char *expected_output, print_func_t2 f, dliststr_t *param);
int valid_hashtable_output_match(char *label, char *expected_output, print_func_t3 f, hash_table_t *param);
int valid_lru_output_match(char *label, char *expected_output, print_func_t4 f, lru_t *param);

#endif
