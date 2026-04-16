#include "lists.h"
/**
 * rev_printlist- prints all elements of a dlistint_t in reverse
 * @h: pointer to head
 * Return: number of nodes
 */
size_t rev_printlist(const dlistint_t *h)
{
	size_t len = 0;

	if (!h)
		return (0);
	while (h->next != NULL)
	{
		len++;
		h = h->next;
	}

	while (h != NULL)
	{
		printf("%d\n", h->n);
		h = h->prev;
	}
	return (len);
}

/**
 * print_dlistint - prints all elements of a dlistint_t list
 * @h: pointer to head
 * Return: number of nodes
 */
size_t print_dlistint(const dlistint_t *h)
{
	size_t len = 0;

	while (h != NULL)
	{
		printf("%d\n", h->n);
		len++;
		h = h->next;
	}
	return (len);
}

/**
 * add_dnodeint - adds a new node at the beginning of a dlistint_t list
 * @head: pointer to pointer to head
 * @n: value to insert
 * Return: address of new element, or NULL on failure
 */
dlistint_t *add_dnodeint(dlistint_t **head, const int n)
{
	dlistint_t *new_node, *lru;
	int i = 0;

	if (head == NULL)
		return (NULL);

	new_node = malloc(sizeof(dlistint_t));
	if (new_node == NULL)
		return (NULL);

	new_node->n = n;
	new_node->prev = NULL;
	new_node->next = *head;

	if (*head != NULL)
		(*head)->prev = new_node;

	*head = new_node;

	if (dlist_len(*head) > 5)
	{
		lru = *head;

		while (lru->next)
			lru = lru->next;

		if (lru->prev)
			lru->prev->next = NULL;
		free (lru);
	}

	return (new_node);
}

/**
 * delete_dnodeint_at_index - deletes node at given index
 * @head: pointer to pointer to head
 * @index: index of node to delete
 * Return: 1 on success, -1 on failure
 */
int delete_dnodeint_at_index(dlistint_t **head, unsigned int index)
{
	dlistint_t *current;
	unsigned int i = 0;

	if (head == NULL || *head == NULL)
		return (-1);

	current = *head;

	while (current != NULL)
	{
		if (i == index)
		{
			if (current->prev)
				current->prev->next = current->next;
			else
				*head = current->next;

			if (current->next)
				current->next->prev = current->prev;

			free(current);
			return (1);
		}
		current = current->next;
		i++;
	}

	return (-1);
}

static size_t dlist_len(dlistint_t *head)
{
    size_t i = 0;

    while (head)
    {
        i++;
        head = head->next;
    }
    return i;
}
