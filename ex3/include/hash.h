#ifndef HASH_H
#define HASH_H

#define MAX_WORD_LENGTH 100
#define TABLE_SIZE 10007 // Cambiato a un numero primo più grande per ridurre le collisioni

typedef struct Node {
    void* key;
    void* value;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node** buckets;
    int size;
    int (*compare)(const void*, const void*);
    unsigned long (*hash_function)(const void*);
    size_t key_size;
    size_t value_size;
} HashTable;

/**
 * @brief Processes a source file for a given word length.
 * @param src Input file.
 * @param lenghtWord Maximum word length.
 */
void processFile(FILE *src, const size_t lenghtWord);

/**
 * @brief Comparison function for string keys (case-insensitive).
 * @param a Pointer to the first key.
 * @param b Pointer to the second key.
 * @return 0 if equal, <0 if a < b, >0 if a > b.
 */
int key_compare(const void* a, const void* b);

/**
 * @brief Hash function for strings.
 * @param key Pointer to the string.
 * @return Hash value.
 */
unsigned long hash_string(const void* key);

/**
 * @brief Creates a new hash table.
 * @param key_compare Function to compare keys.
 * @param hash_func Function to hash the key.
 * @return Pointer to the new HashTable.
 */
HashTable* hash_table_create(int (*key_compare)(const void*, const void*), unsigned long (*hash_func)(const void*));

/**
 * @brief Inserts a key-value pair into the hash table.
 * @param table Pointer to the HashTable.
 * @param key Pointer to the key.
 * @param value Pointer to the value.
 */
void hash_table_put(HashTable* table, const void* key, const void* value);

/**
 * @brief Retrieves the value associated with a key in the hash table.
 * @param table Pointer to the HashTable.
 * @param key Pointer to the key.
 * @return Pointer to the value, or NULL if the key does not exist.
 */
void* hash_table_get(const HashTable* table, const void* key);

/**
 * @brief Checks if a key exists in the hash table.
 * @param table Pointer to the HashTable.
 * @param key Pointer to the key.
 * @return 1 if the key exists, 0 otherwise.
 */
int hash_table_contains_key(const HashTable* table, const void* key);

/**
 * @brief Removes a key-value pair from the hash table.
 * @param table Pointer to the HashTable.
 * @param key Pointer to the key.
 */
void hash_table_remove(HashTable* table, const void* key);

/**
 * @brief Returns the number of elements in the hash table.
 * @param table Pointer to the HashTable.
 * @return Number of elements.
 */
int hash_table_size(const HashTable* table);

/**
 * @brief Returns all keys present in the hash table.
 * @param table Pointer to the HashTable.
 * @return Array of pointers to the keys.
 */
void** hash_table_keyset(const HashTable* table);

/**
 * @brief Frees the memory allocated for the hash table.
 * @param table Pointer to the HashTable.
 */
void hash_table_free(HashTable* table);

/**
 * @brief Comparison function for strings (case-insensitive).
 * @param a Pointer to the first string.
 * @param b Pointer to the second string.
 * @return 0 if equal, <0 if a < b, >0 if a > b.
 */
int compare_strings(const void* a, const void* b);

/**
 * @brief Hash function for strings.
 * @param key Pointer to the string.
 * @return Hash value.
 */
unsigned long hash_string(const void* key);

/**
 * @brief Comparison function for integers.
 * @param a Pointer to the first integer.
 * @param b Pointer to the second integer.
 * @return 0 if equal, <0 if a < b, >0 if a > b.
 */
int compare_ints(const void* a, const void* b);

/**
 * @brief Hash function for integers.
 * @param key Pointer to the integer.
 * @return Hash value.
 */
unsigned long hash_int(const void* key);

/**
 * @brief Prints all key-value pairs sorted by descending value and then alphabetically.
 * @param table Pointer to the HashTable.
 */
void hash_table_print_sorted(const HashTable* table);

/**
 * @brief Comparison function for nodes (for sorting).
 * @param a Pointer to the first node.
 * @param b Pointer to the second node.
 */
void compare_nodes(const void* a, const void* b);

/**
 * @brief Comparison function for nodes: first by descending value, then alphabetically.
 * @param a Pointer to the first node.
 * @param b Pointer to the second node.
 * @return <0, 0, >0 depending on order.
 */
int compare_nodes_desc_alpha(const void* a, const void* b);

#endif