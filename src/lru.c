#include "lru.h"

char *get_from_cache(lru_t *lru, char *key)
{
	dliststr_node_t *value = NULL;

	value = hash_table_get(&(lru->hashtable), key);

	if (!value)
	{
		return (NULL);
	}

	move_dnodestr_to_front(&(lru->dlist), value);
	return (value->value);
}

void set_in_cache(lru_t *lru, char *key, char *value)
{
	dliststr_node_t *node = add_dnodestr_in_front(&(lru->dlist), key, value);
	hash_table_set(&(lru->hashtable), key, node);

	if ((lru->dlist).length > MAX_LENGTH)
	{
		delete_last_dnodestr(&(lru->dlist));
		hash_table_remove_element(key);
	}
}

void print_cache(lru_t *lru)
{
	print_dliststr(&(lru->dlist));
	hash_table_print(&(lru->hashtable));
}
