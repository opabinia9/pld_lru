#include "test.h"

FILE *capture_stdout_to_file(print3_func_t f, void *param)
{
	FILE *tmp = tmpfile();
	int stdout_fd;

	if (!tmp)
	{
		return (NULL);
	}

	stdout_fd = dup(STDOUT_FILENO);
    dup2(fileno(tmp), STDOUT_FILENO);

    f(param);
    fflush(stdout);

    dup2(stdout_fd, STDOUT_FILENO);
    close(stdout_fd);

    rewind(tmp);

	return (tmp);	
}

char *copy_file_to_buffer(FILE *tmp)
{
	char *buf;
	long size;

	fseek(tmp, 0, SEEK_END);
    size = ftell(tmp);
    rewind(tmp); 
	
	buf = malloc(size + 1);
    if (!buf) {
        fclose(tmp);
        return (NULL);
    }

    fread(buf, 1, size, tmp);
    buf[size] = '\0';

	return (buf);
}

int valid_dlist_output_match(char *label, char *expected_output, print_func_t f, dlistint_t *param)
{
	static int counter = 0;
	int match = 0;
	char *buf;
	FILE *tmp;

	fflush(stdout); 

	tmp = capture_stdout_to_file((print3_func_t)f, (void *)param);
	if (!tmp)
	{
		return (-1);
	}
    
    buf = copy_file_to_buffer(tmp);
    if (!buf)
	{
        return (-1);
    }

    match = (strcmp(buf, expected_output) == 0);

	counter = counter + 1;
	printf("****\t[ DLIST ]Test number: %d\t****\n", counter);
	printf("%s\n", label);
	if (match == 1)
	{
		printf("****\tSuccess! Result: %d\t****\n", match);
	}
	else
	{
		printf("/!\\++++\tFailed! Result: %d\t++++/!\\\t\n", match);
	}
	fflush(stdout); 

    free(buf);
	fclose(tmp);
    return (match);
}


int valid_hashtable_output_match(char *label, char *expected_output, print2_func_t f, hash_table_t *param)
{
	static int counter = 0;
	int match = 0;
	char *buf;
	FILE *tmp;

	fflush(stdout);

	tmp = capture_stdout_to_file((print3_func_t)f, (void *)param);
	if (!tmp)
	{
	 	return (-1);
	}
    
    buf = copy_file_to_buffer(tmp);
    if (!buf)
	{
		return (-1);
	}

	match = (strcmp(buf, expected_output) == 0);

	counter = counter + 1;
	printf("****\t[ HASHTABLE ]Test number: %d\t****\n", counter);
	printf("%s\n", label);
	if (match == 1)
	{
	 	printf("****\tSuccess! Result: %d\t****\n", match);
	}
	else
	{
		printf("/!\\++++\tFailed! Result: %d\t++++/!\\\t\n", match);
		printf("/!\\++++\tReceived: %s\t++++/!\\\t\n", buf);
		printf("/!\\++++\tExpected: %s\t++++/!\\\t\n", expected_output);
	}
	fflush(stdout);

	free(buf);
	fclose(tmp);
    return (match);
}
