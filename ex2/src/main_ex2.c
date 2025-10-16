#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/edit.h"

int main(int argc, char **argv) {
    if (argc < 3 || argv == NULL) {
        puts("Argomenti non validi!");
        return 1;
    }

    FILE *dictionary = fopen(argv[1], "r");
    if (dictionary == NULL) {
        puts("Il primo file non esiste!");
        return 1;
    }

    FILE *correctme = fopen(argv[2], "r");
    if (correctme == NULL) {
        puts("Il secondo file non esiste!");
        return 1;
    }

    correctFile(dictionary, correctme);
    
    puts("\nALL DONE!");

    return 0;
}