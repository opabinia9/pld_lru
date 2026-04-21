#include "hashtable.h"

/**
 * hash_table_create - create a hash table
 * @size: size of hash table array
 * Return: pointer to hash table
 */
hash_table_t *hash_table_create(unsigned long int size)
{
	unsigned long int i = 0;
	hash_table_t *hasht = malloc(sizeof(hash_table_t));

	if (hasht == NULL)
		return (NULL);

	hasht->array = malloc(size * sizeof(*hasht->array));
	if (hasht->array == NULL)
	{
		free(hasht);
		return (NULL);
	}
	while (i < size)
	{
		hasht->array[i] = NULL;
		i++;
	}

	hasht->size = size;

	return (hasht);
}

/**
 * hash_djb2 - hash a string with the sjb2 algorithm
 * @str: string to hash
 * Return: hash of str
 */
unsigned long int hash_djb2(const unsigned char *str)
{
	unsigned long int hash;
	int c;

	hash = 5381;
	while ((c = *str++))
	{
	hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return (hash);
}

/**
 * key_index - generate index for hash_table for a key
 * @key: the key
 * @size: the size of the array of the hash table
 * Return: index
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	unsigned long int idx = hash_djb2(key);

	if (!size)
		return (0);

	idx %= size;

	return (idx);
}

/**
 * hash_table_set - adds an entry to a hash table
 * @ht: hash table to add to
 * @key: key for entry
 * @value: value for entry
 * Return: 1 on success otherwise 0
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	int idx;
	hash_node_t *node;
	hash_node_t *lhead;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);
	node = malloc(sizeof(*node));
	if (node == NULL)
		return (0);
	node->key = strdup(key);
	node->value = strdup(value);
	node->next = NULL;

	idx = key_index((const unsigned char *)key, ht->size);

	if (ht->array[idx] == NULL)
		ht->array[idx] = node;
	else
	{
		lhead = ht->array[idx];
		while (lhead != NULL)
		{
			if (!strcmp(lhead->key, key))
			{
				free(lhead->value);
				lhead->value = node->value;
				free(node->key);
				free(node);
				return (1);
			}
			else
				lhead = lhead->next;
		}
		node->next = ht->array[idx];
		ht->array[idx] = node;
	}
	return (1);
}

/**
 * hash_table_get - get a value from a hash table
 * @ht: the hash table you want to look into
 * @key: the key you are looking for
 * Return: value aociated with key or NULL on fail
 */
char *hash_table_get(const hash_table_t *ht, const char *key)
{
	unsigned long int idx;
	hash_node_t *lhead;

	if (ht == NULL || key == NULL)
		return (NULL);

	idx = key_index((const unsigned char *)key, ht->size);
	lhead = ht->array[idx];
	while (lhead)
	{
		if (!strcmp(lhead->key, key))
		{
			return (lhead->value);
		}
		lhead = lhead->next;
	}
	return (NULL);
}

/**
 * hash_table_print - print a hash table;
 * @ht: hash table to print
 */
size_t hash_table_print(const hash_table_t *ht)
{
	size_t idx = 0;
	int i = 0;
	hash_node_t *lhead;

	printf("{");

	while (idx < ht->size)
	{
		lhead = ht->array[idx];
		while (lhead)
		{
			if (i)
				printf(", ");
			printf("'%s': '%s'", lhead->key, lhead->value);
			lhead = lhead->next;
			i = 1;
		}
		idx++;
	}

	printf("}");
	return (idx);
}

/**
 * hash_table_delete - deltes a given hash table
 * @ht: hash table to delete
 */
void hash_table_delete(hash_table_t *ht)
{
	unsigned long int idx = 0;
	hash_node_t *lhead, *temp;

	while (idx < ht->size)
	{
		lhead = ht->array[idx];
		while (lhead)
		{
			temp = lhead->next;
			free(lhead->key);
			free(lhead->value);
			free(lhead);
			lhead = temp;
		}
		idx++;
	}
	free(ht->array);
	free(ht);
}
