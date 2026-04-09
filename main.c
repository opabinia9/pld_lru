#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
typedef struct node_t
{
	char *n;
	node_t *next;
	node_t *last;
} node_t;
*/

char *get_data(char *key)
{
	int len = rand() % 10;
	int n = 0;
	char *str = malloc((len) * sizeof(*str));

	if (key == NULL)
		return (NULL);
	
	while (n < len)
	{
		str[n] = (rand() % (90 - 65)) + 65;
		n++;
	}
	
	return (str);	
}

int main(int argc, char *argv[])
{
/**	int i = 5;

	node_t head = NULL;
	
	while (n < i)
	{
		node_t *node_p = malloc(sizeof(*node_p));
		
		node_p->n = "word1";
		node_p->last = head;
		node_p->next = NULL;
	}
*/

	srand(time(NULL));
	printf("str == %s\n", get_data("five"));
	printf("str == %s\n", get_data("five"));
	printf("str == %s\n", get_data("five"));

	return (0);
}

