#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../lib/Unity/src/unity.h"
#include "../include/hash.h"


int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

unsigned long hash_int(const void* key) {
    return (unsigned long)(*(int*)key);
}

HashTable* table;

void setUp(void) {
    table = hash_table_create(compare_ints, hash_int);
}

void tearDown(void) {
    hash_table_free(table);
}

// Test inserimento e recupero
void test_hash_table_put_and_get(void) {
    const char* key = "testkey";
    int* value = malloc(sizeof(int));
    *value = 42;

    hash_table_put(table, key, value);
    int* retrieved = (int*) hash_table_get(table, key);
    TEST_ASSERT_NOT_NULL(retrieved);
    TEST_ASSERT_EQUAL_INT(42, *retrieved);

    free(value); // La hash table copia il valore, quindi si può liberare qui
}

// Test presenza chiave
void test_hash_table_contains_key(void) {
    const char* key = "present";
    int* value = malloc(sizeof(int));
    *value = 100;

    hash_table_put(table, key, value);
    TEST_ASSERT_TRUE(hash_table_contains_key(table, key));

    free(value); // La hash table copia il valore, quindi si può liberare qui
}

// Test rimozione chiave
void test_hash_table_remove(void) {
    int* key = malloc(sizeof(int));
    int* value = malloc(sizeof(int));
    *key = 7;
    *value = 77;

    hash_table_put(table, key, value);
    hash_table_remove(table, key);
    TEST_ASSERT_FALSE(hash_table_contains_key(table, key));

    // Do not free key and value here; hash_table_free will handle it
}

// Test dimensione
void test_hash_table_size(void) {
    int* key1 = malloc(sizeof(int));
    int* key2 = malloc(sizeof(int));
    int* key3 = malloc(sizeof(int));
    int* value1 = malloc(sizeof(int));
    int* value2 = malloc(sizeof(int));
    int* value3 = malloc(sizeof(int));

    *key1 = 1; *value1 = 10;
    *key2 = 2; *value2 = 20;
    *key3 = 3; *value3 = 30;

    hash_table_put(table, key1, value1);
    hash_table_put(table, key2, value2);
    hash_table_put(table, key3, value3);

    TEST_ASSERT_EQUAL_INT(3, hash_table_size(table));

    // Do not free keys and values here; hash_table_free will handle it
}

// Test recupero insieme delle chiavi
void test_hash_table_keyset(void) {
    int* key1 = malloc(sizeof(int));
    int* key2 = malloc(sizeof(int));
    int* key3 = malloc(sizeof(int));
    int* value1 = malloc(sizeof(int));
    int* value2 = malloc(sizeof(int));
    int* value3 = malloc(sizeof(int));

    *key1 = 1; *value1 = 10;
    *key2 = 2; *value2 = 20;
    *key3 = 3; *value3 = 30;

    hash_table_put(table, key1, value1);
    hash_table_put(table, key2, value2);
    hash_table_put(table, key3, value3);

    void** keys = hash_table_keyset(table);
    TEST_ASSERT_NOT_NULL(keys);

    free(keys);
    // Do not free keys and values here; hash_table_free will handle it
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_hash_table_put_and_get);
    RUN_TEST(test_hash_table_contains_key);
    RUN_TEST(test_hash_table_remove);
    RUN_TEST(test_hash_table_size);
    RUN_TEST(test_hash_table_keyset);
    return UNITY_END();
}
