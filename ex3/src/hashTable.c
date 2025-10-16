#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/hash.h"

int key_compare(const void* a, const void* b) {
    return strcasecmp((const char*)a, (const char*)b);
}

unsigned long hash_string(const void* key) {
    unsigned long hash = 5381;
    const char* str = (const char*)key;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; 
    return hash;
}

HashTable* hash_table_create(int (*compare)(const void*, const void*), unsigned long (*hash_function)(const void*)) {
    HashTable* table = malloc(sizeof(HashTable));
    if (!table) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    table->size = TABLE_SIZE;
    table->buckets = calloc(table->size, sizeof(Node*));
    if (!table->buckets) {
        perror("Memory allocation failed");
        free(table);
        exit(EXIT_FAILURE);
    }

    table->compare = compare;
    table->hash_function = hash_function;
    
    if (hash_function == hash_string || compare == key_compare) 
        table->key_size = 0; 
    else 
        table->key_size = sizeof(int);
    
    return table;
}

void hash_table_put(HashTable* table, const void* key, const void* value) {
    unsigned long index = table->hash_function(key) % table->size;
    Node* current = table->buckets[index];
    while (current) {
        if (table->compare(key, current->key) == 0) {
            current->value = (void*)value;
            return;
        }
        current = current->next;
    }
    
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    
    size_t key_size = table->key_size;
    if (key_size == 0) {
        key_size = strlen((const char*)key) + 1;
    }
    
    new_node->key = malloc(key_size);
    if (!new_node->key) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    
    memcpy(new_node->key, key, key_size);
    new_node->value = (void*)value;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

void* hash_table_get(const HashTable* t, const void* key) {
    unsigned long index = t->hash_function(key) % t->size;
    for (Node* current = t->buckets[index]; current; current = current->next) {
        if (t->compare(key, current->key) == 0) 
            return current->value;
    }
    return NULL;
}

void hash_table_free(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        Node* current = table->buckets[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

int hash_table_contains_key(const HashTable* t, const void* key) {
    return hash_table_get(t, key) != NULL;
}

void hash_table_remove(HashTable* t, const void* key) {
    unsigned long index = t->hash_function(key) % t->size;
    Node* current = t->buckets[index];
    Node* prev = NULL;
    
    while (current) {
        if (t->compare(key, current->key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                t->buckets[index] = current->next;
            }
            free(current->key);
            
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int hash_table_size(const HashTable* t) {
    int count = 0;
    
    for (int i = 0; i < t->size; i++) {
        Node* current = t->buckets[i];
        while (current) {
            count++;
            current = current->next;
        }
    }
    
    return count;
}

void** hash_table_keyset(const HashTable* t) {
    int count = hash_table_size(t);
    void** keys = malloc((count + 1) * sizeof(void*)); 
    int idx = 0;
    
    for (int i = 0; i < t->size; i++) {
        Node* current = t->buckets[i];
        while (current) {
            keys[idx++] = current->key;
            current = current->next;
        }
    }
    
    keys[idx] = NULL; 
    
    return keys;
}

int compare_nodes_desc_alpha(const void* a, const void* b) {
    const Node* na = *(const Node**)a;
    const Node* nb = *(const Node**)b;
    int va = *(int*)(na->value);
    int vb = *(int*)(nb->value);
    
    if (vb != va) {
        return vb - va;
    }
    
    return strcasecmp((const char*)na->key, (const char*)nb->key);
}

void hash_table_print_sorted(const HashTable* table) {
    int count = hash_table_size(table);
    if (count == 0) {
        printf("Hash table is empty.\n");
        return;
    }

    Node** nodes = malloc(count * sizeof(Node*));
    int idx = 0;
    for (int i = 0; i < table->size; i++) {
        Node* current = table->buckets[i];
        while (current) {
            nodes[idx++] = current;
            current = current->next;
        }
    }

    qsort(nodes, count, sizeof(Node*), compare_nodes_desc_alpha);

    printf("Word\t\tCount\n");
    printf("-------------------------\n");
    for (int i = 0; i < count; i++) {
        if (*(int*)nodes[i]->value < 1) {
            continue;
        }
        printf("%s\t\t%d\n", (char*)nodes[i]->key, *(int*)nodes[i]->value);
    }

    free(nodes);
}