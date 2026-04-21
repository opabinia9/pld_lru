CC = gcc
CFLAGS = -Wall -Wextra -I./include
RM = rm -f

SRC_DIR = src
TEST_DIR = tests

MAIN_TARGET = lru_cache
DLIST_TARGET = dlist_test
HASHTABLE_TARGET = hashtable_test

all: $(MAIN_TARGET) tests

tests: $(DLIST_TARGET) $(HASHTABLE_TARGET)

$(MAIN_TARGET): $(SRC_DIR)/main.c $(SRC_DIR)/dlist.c $(SRC_DIR)/hashtable.c
	$(CC) $(CFLAGS) $^ -o app

$(DLIST_TARGET): $(TEST_DIR)/test.c $(TEST_DIR)/test_dlist.c $(SRC_DIR)/dlist.c 
	$(CC) $(CFLAGS) $^ -o $@

$(HASHTABLE_TARGET): $(TEST_DIR)/test.c $(TEST_DIR)/test_hashtable.c $(SRC_DIR)/hashtable.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(MAIN_TARGET) $(DLIST_TARGET) $(HASHTABLE_TARGET)
	find . -name "*~" -type f -delete

re: clean all

.PHONY: all dlist hash clean reCC = gcc
