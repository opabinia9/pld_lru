#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *get_data(char *key)
{
	int len = (rand() % 10) + 1;
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
	int i = 0;
	if (argc < 3)
		return (1);

	srand(time(NULL));

	while (i < atoi(argv[1]))
	{
		printf("str == %s\n", get_data("five"));
		i++;
	}
	return (0);
}

