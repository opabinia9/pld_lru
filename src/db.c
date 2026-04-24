#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "db.h"

void micro_delay() {
    struct timespec ts;
    
    // Set delay to 0 seconds and 100,000,000 nanoseconds (0.1 seconds)
    ts.tv_sec = 0;
    ts.tv_nsec = 1; 

    // The second argument (NULL) is for "remaining time" if interrupted by a signal
    nanosleep(&ts, NULL);
}

char* find_value_by_key(const char* filename, const char* search_key) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    char* result_value = NULL;

    while (fgets(line, sizeof(line), file)) {
		micro_delay();
        line[strcspn(line, "\n")] = 0;

        char* key = strtok(line, ";");
        char* value = strtok(NULL, ";");

        if (key && value) {
            if (strcmp(key, search_key) == 0) {
                result_value = strdup(value);
                break;
            }
        }
    }

    fclose(file);
    return (result_value);
}

