#include "test.h"

FILE *capture_stdout_to_file(list_func_t f, dlistint_t *list)
{
	FILE *tmp = tmpfile();
	int stdout_fd;

	if (!tmp)
	{
		return (NULL);
	}

	stdout_fd = dup(STDOUT_FILENO);
    dup2(fileno(tmp), STDOUT_FILENO);

    f(list);
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

int valid_output_match(char *label, char *expected_output, list_func_t f, dlistint_t *list)
{
	static int counter = 0;
	int match = 0;
	char *buf;
	FILE *tmp;

	fflush(stdout); 

	tmp = capture_stdout_to_file(f, list);
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
	printf("****\tTest number: %d\t\t****\n", counter);
	printf("%s\n", label);
	printf("****\tResult [expected 1]: %d\t****\n", match);
	fflush(stdout); 

    free(buf);
	fclose(tmp);
    return (match);
}
