#ifndef __DLIST_H__
#define __DLIST_H__

/**
 * struct dlistint_s - doubly linked list
 * @n: integer
 * @prev: points to the previous node
 * @next: points to the next node
 *
 * Description: doubly linked list node structure
 * 
 */
typedef struct dlistint_node_s
{
    int n;
    struct dlistint_node_s *prev;
    struct dlistint_node_s *next;
}	dlistint_node_t;

typedef struct dlistint_s
{
	size_t length;
	struct dlistint_node_s *head;
}	dlistint_t;

size_t print_dlistint(dlistint_t *list);
size_t rev_print_dlistint(dlistint_t *list);
dlistint_node_t *add_dnodeint(dlistint_t *list, const int n);
int delete_dnodeint_at_index(dlistint_t *list, unsigned int index);
void delete_last_dnodeint(dlistint_t *list);
void move_dnodeint_to_front(dlistint_t *list, dlistint_node_t *node);

#define MAX_LENGTH 5

#endif
