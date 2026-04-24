#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "db.h"
#include "lru.h"

int main(int argc, char **argv) {
    char search_term[KEY_BUFFER];
	struct timespec start, end;
	lru_t *lru_cache = NULL;
	char *val = NULL;
	int index = 1;

	if (argc == 2 && strcmp(argv[1], "1") == 0)
	{
		lru_cache = malloc(sizeof(*lru_cache));
		if (!lru_cache)
		{
			return (0);
		}
		
		lru_cache->hashtable.size = 255;
		lru_cache->hashtable.array = malloc(sizeof(*(lru_cache->hashtable.array)) * lru_cache->hashtable.size);
		lru_cache->dlist.length = 0;
		lru_cache->dlist.head = NULL;
	}

    printf("--- Database Search Tool ---\n");
	printf("--- Cache enabled: %s ---\n", (lru_cache != NULL ? "TRUE" : "FALSE"));
    printf("Press Ctrl+C to exit at any time.\n");

    while (1) {
        printf("\n[ %i ] Enter key to search: ", index);
        
        // Read input and check for EOF (Ctrl+D)
        if (scanf("%99s", search_term) == EOF) {
            printf("\nExiting...\n");
            break;
        }

		// Start the clock
        clock_gettime(CLOCK_MONOTONIC, &start);

		if (lru_cache != NULL)
		{
			val = get_from_cache(lru_cache, search_term);
	   
			if (val == NULL)
			{
				val = find_value_by_key(DB_FILE, search_term);
				set_in_cache(lru_cache, search_term, val);
			}
		}
		clock_gettime(CLOCK_MONOTONIC, &end);
		
		// Calculate time elapsed in seconds
		double time_taken = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) / 1000000000.0;
		
        if (val) {
            printf(">> Result: %s\n", val);
        } else {
            printf(">> Key '%s' not found.\n", search_term);
        }
		
		printf(">> Search took: %.6f seconds\n", time_taken);
		index++;
    }

    return 0;
}
