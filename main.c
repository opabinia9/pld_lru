#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<unistd.h>

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
	clock_t start = clock();

	if (atoi(argv[2]))
		printf("cache on\n");
	else
		printf("cache off\n");

	while (i < atoi(argv[1]))
	{
		printf("str == %s\n", get_data("five"));
		i++;
	}

	clock_t end = clock();
	double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\nprocessed %s element(s) in %f seconds\n", argv[1], cpu_time_used);
	return (0);
}

