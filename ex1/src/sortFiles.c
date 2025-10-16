#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../include/sort.h"

long int findSize(FILE *fp) {
    if (fp == NULL) return -1;

    char a[1024];
    int count = 0;

    while (!feof(fp)) {
        if (fgets(a, sizeof(a), fp) != NULL) 
            count++;
    }

    return count;
}

void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo) {
    if (infile == NULL || outfile == NULL) {
        perror("File infile/outfile error!");
        exit(1);
    }

    const long int size = findSize(infile);
    if (size < 0) {
        perror("Error size!");
        exit(1);
    }

    if (field > 3 || field < 1) {
        perror("Field doesn't exist!");
        exit(1);
    }

    Records *rec = malloc(size * sizeof(Records));
    if (rec == NULL) {
        perror("Records malloc Error");
        fclose(infile);
        exit(1);
    }

    rewind(infile);

    char line[400];
    int i = 0;

    while ((fgets(line, sizeof(line), infile) != NULL) && i < size) {
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, ",");
        if (token != NULL)
            rec[i].id = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(rec[i].name, token, sizeof(rec[i].name) - 1);
            rec[i].name[sizeof(rec[i].name) - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token != NULL)
            rec[i].integerNum = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL) {
            while (*token == ' ') token++;
            rec[i].floatNum = strtof(token, NULL);
        }

        i++;
    }
    fclose(infile);


    clock_t start = clock();
    switch (algo) {
        case 1:
            if (field == 1) 
                merge_sort(rec, i, sizeof(Records), compar_name);
            
            if (field == 2)
                merge_sort(rec, i, sizeof(Records), compar_integerNum);
            
            if (field == 3)
                merge_sort(rec, i, sizeof(Records), compar_floatNum);
            
            break;

        case 2: 
            if (field == 1) 
                quick_sort(rec, i, sizeof(Records), compar_name);
            
            if (field == 2)
                quick_sort(rec, i, sizeof(Records), compar_integerNum);
            
            if (field == 3)
                quick_sort(rec, i, sizeof(Records), compar_floatNum);
            
            break;

        default:
            perror("Algorithm doesn't exist!");
            free(rec);
            exit(1);
    }
    
    clock_t end = clock();
    double tot = (double)(end - start) / CLOCKS_PER_SEC; 
    printf("Sorting completed in %.2f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    for (int j = 0; j < i; j++) 
        fprintf(outfile, "%d,%s,%d,%.2f\n", rec[j].id, rec[j].name, rec[j].integerNum, rec[j].floatNum);
    
    end = clock();
    printf("Printing completed in %.2f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);

    tot += (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tot: %.2f seconds.\n", tot);
    
    free(rec);
    fclose(outfile);
    
    return;
}