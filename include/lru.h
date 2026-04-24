#ifndef __LRU_H__
#define __LRU_H__

#include "dlist.h"
#include "hashtable.h"

#define MAX_LENGTH 5

typedef struct lru_s
{
	hash_table_t hashtable;
	dliststr_t dlist;
} lru_t;

char *get_from_cache(lru_t *lru, char *key);
void set_in_cache(lru_t *lru, char *key, char *value);
void print_cache(lru_t *lru);

#endif
