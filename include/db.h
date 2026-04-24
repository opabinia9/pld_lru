#ifndef __DB_H__
#define __DB_H__

#define MAX_LINE_LENGTH 256
#define KEY_BUFFER 100
#define DB_FILE "unique_data.txt"

char* find_value_by_key(const char* filename, const char* search_key);

#endif
