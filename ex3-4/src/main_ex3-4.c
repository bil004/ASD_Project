#include <stdio.h>
#include <stdlib.h>

// $ ./main_ex3-4 italian_dist_graph.csv torino output.txt

#include "../include/graph.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        puts("Insufficient arguments!");
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    if (src == NULL) {
        puts("Errore nell'apertura del file!");
        return 1;
    }

    FILE *result = fopen(argv[3], "w");
    if (result == NULL) {
        puts("Errore nella creazione del file!");
        return 1;
    }

    bsf(src, argv[2], result);
    puts("ALL DONE!");
    
    return 0;
}