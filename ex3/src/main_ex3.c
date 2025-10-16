#include <stdio.h>
#include <stdlib.h>

#include "../include/hash.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        puts("Incorrect number of arguments!");
        return 1;
    }

    if (atoi(argv[2]) <= 0) {
        puts("Incorrect lenght!");
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    if (src == NULL) {
        puts("File doesn't exist!");
        return 1;
    }

    processFile(src, atoi(argv[2]));
    puts("ALL DONE!");

    return 0;
}