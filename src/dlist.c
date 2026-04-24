 #include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dlist.h"

dliststr_node_t *create_node(char *key, char *value)
{
	dliststr_node_t *new_node;

	new_node = malloc(sizeof(*new_node));
	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->prev = new_node;
	new_node->next = new_node;

	return (new_node);
}

void free_node(dliststr_node_t *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void print_dliststr(dliststr_t *list)
{
	size_t len = 0;
	dliststr_node_t *node;

	node = list->head;
	while (len < list->length)
	{
		printf("%s\n", node->value);
		node = node->next;
		len = len + 1;
	}
}

void rev_print_dliststr(dliststr_t *list)
{
	size_t len = 0;
	dliststr_node_t *node;

	if (list->length == 0)
	{
		return;
	}

	node = list->head->prev;
	while (len < list->length)
	{
		printf("%s\n", node->value);
		node = node->prev;
		len = len + 1;
	}
}

/**
 * add_dnodeint- prints a list
 * @head: value
 * @n: value
 * Return: address
 */
dliststr_node_t *add_dnodestr_in_front(dliststr_t *list, char *key, char *value)
{
	dliststr_node_t *new_node;

	if (list == NULL)
	{
		return (NULL);
	}

	new_node = create_node(key, value);
	if (!new_node)
	{
		return (NULL);
	}

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

int delete_dnodestr_at_index(dliststr_t *list, unsigned int index)
{
	unsigned int i = 0;
	dliststr_node_t *current;

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

			free_node(current);
			list->length = list->length - 1;
			return (1);
		}
		i++;
		current = current->next;
	}

	return (-1);
}

void delete_last_dnodestr(dliststr_t *list)
{
	dliststr_node_t *to_delete;
	
	if (list->head->prev == list->head)
	{
		free_node(list->head);
		list->head = NULL;
		list->length = list->length - 1;
		return ;
	}

	to_delete = list->head->prev;
	list->head->prev = to_delete->prev;
	to_delete->prev->next = list->head;
	free_node(to_delete);
	list->length = list->length - 1;
}

void move_dnodestr_to_front(dliststr_t *list, dliststr_node_t *node)
{
	dliststr_node_t *prev;
	dliststr_node_t *next;
	dliststr_node_t *last;

	printf("head: %p -> node: %p\n", list->head, node);

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
