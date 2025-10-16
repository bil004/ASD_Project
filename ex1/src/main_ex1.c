#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "../include/sort.h"

int main(int argc, char **argv) {
    if (argc != 5 || argv == NULL) {
        puts("Invalid arguments!");
        return 1;
    }
    
    if (atoi(argv[3]) < 1 || atoi(argv[3]) > 3) {
        puts("Insufficient arguments!");
        return 1;
    }

    if (atoi(argv[4]) < 1 || atoi(argv[4]) > 2) {
        puts("Algorithm does not exist!");
        return 1;
    }

    FILE *records = fopen(argv[1], "r");
    if (records == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *sorted = fopen(argv[2], "w");
    if (sorted == NULL) {
        perror("Error opening output file");
        fclose(records);
        return 1;
    }
    
    sort_records(records, sorted, atoi(argv[3]), atoi(argv[4]));
    puts("Files sorted!");

    return 0;
}