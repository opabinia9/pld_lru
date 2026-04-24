#include "test.h"
#include "lru.h"

int main()
{
	lru_t cache = {
		.hashtable = {
			.size = 10,
			.array = NULL
		},
		.dlist = {
			.length = 0,
			.head = NULL
		}
	};

	cache.hashtable.array = malloc(sizeof(char *) * cache.hashtable.size);
	
	set_in_cache(&cache, "foo", "bar");
	valid_lru_output_match("Test adding foo:bar.",
	 				   "bar\n{'foo': 'bar'}", print_cache, &cache);
	set_in_cache(&cache, "titi", "toto");
	valid_lru_output_match("Test adding titi:toto.",
	 				   "toto\nbar\n{'titi': 'toto', 'foo': 'bar'}", print_cache, &cache);

	char *foo_value = get_from_cache(&cache, "foo");

	printf("****\t[ LRU ] Special Test\t****\n");
	printf("Getting 'foo' value.\n");

	int match = (strcmp(foo_value, "bar") == 0);
	if (match == 1)
	{
	 	printf("****\tSuccess! Result: %d\t****\n", match);
	}
	else
	{
		printf("/!\\++++\tFailed! Result: %d\t++++/!\\\t\n", match);
		printf("/!\\++++\tReceived: %s\t++++/!\\\t\n", foo_value);
		printf("/!\\++++\tExpected: %s\t++++/!\\\t\n", "bar");
	}

	char *undefined_value = get_from_cache(&cache, "not_found");

	printf("****\t[ LRU ] Special Test\t****\n");
	printf("Getting 'not_found' value.\n");

	match = (undefined_value == NULL);
	if (match == 1)
	{
	 	printf("****\tSuccess! Result: %d\t****\n", match);
	}
	else
	{
		printf("/!\\++++\tFailed! Result: %d\t++++/!\\\t\n", match);
		printf("/!\\++++\tReceived: %s\t++++/!\\\t\n", undefined_value);
		printf("/!\\++++\tExpected: %s\t++++/!\\\t\n", "bar");
	}
	

}
