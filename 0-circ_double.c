 #include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lists.h"

#define LEN 5

/**
 * struct dlistint_s - doubly linked list
 * @n: integer
 * @prev: points to the previous node
 * @next: points to the next node
 *
 * Description: circular doubly linked list node structure 
 * 
 */
 

/**
 * print_dlistint- prints a list
 * @h: value
 * Return: number of nodes
 */

size_t print_dlistint(dlistint_t *h)
{
	size_t len = 0;

	while (len < LEN)
	{
		printf("%d\n", h->n);
		len++;
		if (h->next == NULL)
			return (len);
		h = h->next;
	}
	return (len);
	
}

size_t rev_print_dlistint(dlistint_t *h)
{
  size_t len = 0;

  while (len < LEN)
  {
    printf("%d\n", h->n);
    len++;
    h = h->prev;
  }

  return (len);
}

/**
 * add_dnodeint- prints a list
 * @head: value
 * @n: value
 * Return: address
 */
dlistint_t *add_dnodeint(dlistint_t **head, const int n)
{
	dlistint_t *new_node;

	if (head == NULL)
	  return (NULL);

	new_node = malloc(sizeof(dlistint_t));
	if (!new_node)
	{
		free(new_node);
		return (NULL);
	}
	new_node->n = n;
	new_node->prev = new_node;
	new_node->next = new_node;

	if (*head)
	{
	  new_node->next = *head;

	  if ((*head)->prev)
	  {
	    new_node->prev = (*head)->prev;
	    (*head)->prev = new_node;
	    new_node->prev->next = new_node;
	  } else {
	    new_node->prev = *head;
	    (*head)->prev = new_node;
	    (*head)->next = new_node;
	  }
	}
	
	*head = new_node;
	return (new_node);
}

/**
 * delete_dnodeint_at_index- prints a list
 * @head: value
 * @index: valu
 * Return: address
 */

int delete_dnodeint_at_index(dlistint_t **head, unsigned int index)
{
	unsigned int i = 0;
	dlistint_t *current;

	if (!head || !*head)
		return (-1);

	current = *head;

	while (current != NULL)
	{
		if (i == index)
		{
			if (current->prev != NULL)
				current->prev->next = current->next;
			else
				*head = current->next;

			if (current->next != NULL)
				current->next->prev = current->prev;

			free(current);
			return (1);
		}
		i++;
		current = current->next;
	}
	return (-1);
}
