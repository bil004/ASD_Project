#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <time.h>

#include "../include/hash.h"

#define MAX_WORD_LENGTH 100

void processFile(FILE *src, const size_t minL) {
    HashTable* table = hash_table_create(key_compare, hash_string);

    char word[MAX_WORD_LENGTH];
    while (fscanf(src, "%99s", word) != EOF) {
        int len = strlen(word);
        for (int i = 0; i < len; i++) {
            word[i] = tolower(word[i]); 
            if (word[i] == '\xE2') continue;
            if (word[i] < 'a' || word[i] > 'z') word[i] = '\0';
        }

        if (strlen(word) >= minL) {
            int* count = hash_table_get(table, word);
            if (count) {
                (*count)++;
            } else {
                int* new_count = malloc(sizeof(int));
                *new_count = 1;
                hash_table_put(table, strdup(word), new_count);
            }
        }
    }

    fclose(src);

    clock_t start = clock();

    void** keys = hash_table_keyset(table);
    int max_count = 0;
    char* most_frequent_word = NULL;

    for (int i = 0; i < hash_table_size(table); i++) {
        int* count = hash_table_get(table, keys[i]);
        if (count && *count > max_count) {
            max_count = *count;
            most_frequent_word = keys[i];
        }
    }
    clock_t end = clock();
    
    if (most_frequent_word) 
        printf("La parola piu' frequente di lunghezza almeno %lld e': '%s' con %d occorrenze\n", minL, most_frequent_word, max_count);
    else 
        printf("Nessuna parola soddisfa il criterio.\n");
    
    printf("\nAlgorithm ended in %.2f seconds.\n", (double)(end-start)/CLOCKS_PER_SEC);

    free(keys);
    hash_table_free(table);
}