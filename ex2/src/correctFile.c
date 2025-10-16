#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h> 
#include <time.h>

#include "../include/edit.h"

long int findSize(FILE *fp) {
    if (fp == NULL) return -1;

    char a[1024];
    int count = 0;
    while (!feof(fp)) {
        if (fgets(a, sizeof(a), fp) != NULL)
            count++;
    }

    rewind(fp); 
    return count;
}

void deletePunct(char *line) {
    char *src = line, *dst = line;

    while (*src != '\0') {
        if ((*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z') || (*src >= '0' && *src <= '9') || *src == ' ') {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void correctFile(FILE *dictionary, FILE *correctme) {
    if (dictionary == NULL || correctme == NULL) return;

    int size = findSize(dictionary);
    if (size <= 0) {
        puts("File dizionario vuoto!");
        exit(1);
    }

    Dictionary dict;
    dict.words = malloc(size * sizeof(char *));
    if (dict.words == NULL) {
        puts("Errore di allocazione memoria per il dizionario!");
        exit(1);
    }

    dict.count = 0;
    rewind(dictionary);

    char line[400];
    int i = 0;

    while (fgets(line, sizeof(line), dictionary) != NULL && i < size) {
        line[strcspn(line, "\n")] = '\0';

        dict.words[i] = malloc((strlen(line) + 1) * sizeof(char));
        if (dict.words[i] == NULL) {
            puts("Errore di allocazione memoria per una parola del dizionario!");
            for (int j = 0; j < i; j++) 
                free(dict.words[j]);
                
            free(dict.words);
            exit(1);
        }

        strcpy(dict.words[i], line);
        toLowerCase(dict.words[i]); 
        dict.count++;
        i++;
    }

    int size2 = findSize(correctme);
    if (size2 <= 0) {
        puts("File da correggere vuoto!");
        exit(1);
    }
    rewind(correctme);

    puts("Parola trovata\t\tParola corretta\t\tEdit Distance");
    puts("------------------------------------------------------------------");

    char *w, *wCorrect;
    int result;

    clock_t start = clock();
    while (fgets(line, sizeof(line), correctme) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        deletePunct(line);

        w = strtok(line, " ");
        while (w != NULL) {
            toLowerCase(w);
            puts("\n");
            printf("Parola da correggere: %s\n", w); 

            int min = INT_MAX;
            wCorrect = NULL;
            for (int i = 0; i < dict.count; i++) {
                result = edit_distance_dyn(dict.words[i], w);

                if (result < min) {                 
                    min = result;
                    if (wCorrect != NULL) free(wCorrect);
                    wCorrect = malloc((strlen(dict.words[i]) + 1) * sizeof(char));
                    if (wCorrect == NULL) {
                        perror("Errore di allocazione memoria per wCorrect");
                        exit(1);
                    }
                    strcpy(wCorrect, dict.words[i]);
                }
            }
            
            printf("%s\t\t%s\t\t%d\n", w, wCorrect, min);
            
            w = strtok(NULL, " ");
        }
    }
    clock_t end = clock();

    printf("\nEdit distance completed in: %.2f secs", (double)(end - start)/CLOCKS_PER_SEC);

    for (int j = 0; j < dict.count; j++)
        free(dict.words[j]);
    
    free(dict.words);
}