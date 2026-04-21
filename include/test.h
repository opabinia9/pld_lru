#ifndef __TEST_H__
#define __TEST_H__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "dlist.h"

typedef size_t (*list_func_t)(dlistint_t *);

int valid_output_match(char *label, char *expected_output, list_func_t f, dlistint_t *list);

#endif
