#ifndef __DLIST_H__
#define __DLIST_H__

#include <stdlib.h>

/**
 * struct dlistint_s - doubly linked list
 * @n: integer
 * @prev: points to the previous node
 * @next: points to the next node
 *
 * Description: doubly linked list node structure
 * 
 */
typedef struct dliststr_node_s
{
	char *key;
    char *value;
    struct dliststr_node_s *prev;
    struct dliststr_node_s *next;
}	dliststr_node_t;

typedef struct dliststr_s
{
	size_t length;
	dliststr_node_t *head;
}	dliststr_t;

void print_dliststr(dliststr_t *list);
void rev_print_dliststr(dliststr_t *list);
dliststr_node_t *add_dnodestr_in_front(dliststr_t *list, char *key, char *value);
int delete_dnodestr_at_index(dliststr_t *list, unsigned int index);
void delete_last_dnodestr(dliststr_t *list);
void move_dnodestr_to_front(dliststr_t *list, dliststr_node_t *node);
dliststr_node_t *create_node(char *key, char *value);

#endif
