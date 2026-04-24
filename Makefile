CC = gcc
CFLAGS = -Wall -Wextra -I./include
RM = rm -f

SRC_DIR = src
TEST_DIR = tests

MAIN_TARGET = lru_cache
TEST_DLIST_TARGET = test_dlist
TEST_HASHTABLE_TARGET = test_hashtable
TEST_LRU_TARGET = test_lru

all: $(MAIN_TARGET) tests

tests: $(TEST_DLIST_TARGET) $(TEST_HASHTABLE_TARGET) $(TEST_LRU_TARGET)

$(MAIN_TARGET): $(SRC_DIR)/main.c $(SRC_DIR)/db.c $(SRC_DIR)/dlist.c $(SRC_DIR)/hashtable.c $(SRC_DIR)/lru.c
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_DLIST_TARGET): $(TEST_DIR)/test.c $(TEST_DIR)/test_dlist.c $(SRC_DIR)/dlist.c 
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_HASHTABLE_TARGET): $(TEST_DIR)/test.c $(TEST_DIR)/test_hashtable.c $(SRC_DIR)/hashtable.c $(SRC_DIR)/dlist.c
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_LRU_TARGET): $(TEST_DIR)/test.c $(TEST_DIR)/test_lru.c $(SRC_DIR)/lru.c $(SRC_DIR)/dlist.c $(SRC_DIR)/hashtable.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(MAIN_TARGET) $(TEST_DLIST_TARGET) $(TEST_HASHTABLE_TARGET) $(TEST_LRU_TARGET)
	find . -name "*~" -type f -delete

re: clean all

.PHONY: all dlist hash clean reCC = gcc
