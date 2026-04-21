 #include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dlist.h"

size_t print_dlistint(dlistint_t *list)
{
	size_t len = 0;
	dlistint_node_t *node;

	node = list->head;
	while (len < list->length)
	{
		printf("%d\n", node->n);
		node = node->next;
		len = len + 1;
	}
	return (len);
}

size_t rev_print_dlistint(dlistint_t *list)
{
	size_t len = 0;
	dlistint_node_t *node;

	if (list->length == 0)
	{
		return (0);
	}

	node = list->head->prev;
	while (len < list->length)
	{
		printf("%d\n", node->n);
		node = node->prev;
		len = len + 1;
	}

  return (len);
}

/**
 * add_dnodeint- prints a list
 * @head: value
 * @n: value
 * Return: address
 */
dlistint_node_t *add_dnodeint(dlistint_t *list, const int n)
{
	dlistint_node_t *new_node;

	if (list == NULL)
	{
		return (NULL);
	}
	
	if (list->length == MAX_LENGTH)
	{
		return (NULL);
	}
	
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
	{
		return (NULL);
	}
	
	new_node->n = n;
	new_node->prev = new_node;
	new_node->next = new_node;

	if (list->head)
	{
		new_node->prev = list->head->prev;
		new_node->next = list->head;

		new_node->prev->next = new_node;
		new_node->next->prev = new_node;
	}

	list->head = new_node;
	list->length = list->length + 1;
	return (new_node);
}

int delete_dnodeint_at_index(dlistint_t *list, unsigned int index)
{
	unsigned int i = 0;
	dlistint_node_t *current;

	if (!list)
	{
		return (-1);
	}

	current = list->head;

	while (current != NULL)
	{
		if (i == index)
		{
			if (current->prev != NULL)
			{
				current->prev->next = current->next;
			}
			else
			{
				list->head = current->next;
			}

			if (current->next != NULL)
			{
				current->next->prev = current->prev;
			}

			free(current);
			list->length = list->length - 1;
			return (1);
		}
		i++;
		current = current->next;
	}

	return (-1);
}

void delete_last_dnodeint(dlistint_t *list)
{
	dlistint_node_t *to_delete;
	
	if (list->head->prev == list->head)
	{
		free(list->head);
		list->head = NULL;
		list->length = list->length - 1;
		return ;
	}

	to_delete = list->head->prev;
	list->head->prev = to_delete->prev;
	to_delete->prev->next = list->head;
	list->length = list->length - 1;
}

void move_dnodeint_to_front(dlistint_t *list, dlistint_node_t *node)
{
	dlistint_node_t *prev;
	dlistint_node_t *next;
	dlistint_node_t *last;

	if (list->head == NULL || node == NULL || list->head == node)
	{
		return;
	}

	prev = node->prev;
	next = node->next;
	last = list->head->prev;

	prev->next = next;
	next->prev = prev;

	last->next = node;
	node->prev = last;
	node->next = list->head;
	list->head->prev = node;
	node->next = list->head;
	list->head = node;
}
