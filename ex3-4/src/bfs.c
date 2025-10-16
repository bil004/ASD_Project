#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../include/graph.h"
#include "../include/hash.h"

// Breadth-First Visit: restituisce l'array dei nodi nell'ordine di visita (BFS)
void** breadth_first_visit(Graph gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)) {
    if (!gr || !start || !hash || !compare) return NULL;
    if (!graph_contains_node(gr, start)) return NULL;
    int n = graph_num_nodes(gr);
    void** visit_order = malloc((n + 1) * sizeof(void*));
    int visit_count = 0;
    // Coda per la BFS
    void** queue = malloc((n + 1) * sizeof(void*));
    int front = 0, rear = 0;
    // Tabella hash per i visitati
    HashTable* visited = hash_table_create(compare, hash);
    // Inserisci nodo di partenza
    queue[rear++] = start;
    hash_table_put(visited, start, (void*)1);
    
    while (front < rear) {
        void* node = queue[front++];
        visit_order[visit_count++] = node;
        void** neighbours = graph_get_neighbours(gr, node);
        if (neighbours) {
            for (int i = 0; neighbours[i] != NULL; i++) {
                if (!hash_table_contains_key(visited, neighbours[i])) {
                    queue[rear++] = neighbours[i];
                    if (rear > n + 1) {
                        printf("ERRORE: overflow della coda BFS! rear=%d n=%d\n", rear, n);
                        exit(1);
                    }
                    hash_table_put(visited, neighbours[i], (void*)1);
                }
            }
            free(neighbours);
        }
    }
    visit_order[visit_count] = NULL;
    free(queue);
    hash_table_free(visited);
    return visit_order;
}

void bsf(FILE *src, const char* city, FILE *result) {
    if (!src || !city || !result) return;
    
    // Crea grafo
    Graph gr = graph_create(1, 0, key_compare, hash_string);
    
    clock_t start = clock();
    char line[256];
    char node1[128], node2[128], label[128];
    
    while (fgets(line, sizeof(line), src)) {
        if (sscanf(line, "%127[^,],%127[^,],%127[^\n]", node1, node2, label) == 3) {
            char *n1 = strdup(node1);
            char *n2 = strdup(node2);
            char *lbl = strdup(label);
            graph_add_node(gr, n1);
            graph_add_node(gr, n2);
            graph_add_edge(gr, n1, n2, lbl);
        }
    }
    clock_t end = clock();
    printf("Reading file and Graph creation completed in %.2f seconds!\n", (float)(end-start)/CLOCKS_PER_SEC);
    
    start = clock();
    
    // Trova il vero puntatore del nodo di partenza
    void **nodes = graph_get_nodes(gr);
    void *start_ptr = NULL;
    for (int i = 0; nodes && nodes[i] != NULL; i++) {
        if (strcasecmp((char*)nodes[i], city) == 0) {
            start_ptr = nodes[i];
            break;
        }
    }
    free(nodes);

    if (start_ptr) {
        void** order = breadth_first_visit(gr, start_ptr, key_compare, hash_string);
        if (order) {
            for (int i = 0; order[i] != NULL; i++) {
                fprintf(result, "%s\n", (char*)order[i]);
            }
            free(order);
        }
    }
    graph_free(gr);
    
    end = clock();
    printf("BFS completed in %.2f seconds!\n", (float)(end-start)/CLOCKS_PER_SEC);
    
    fclose(src);
    fclose(result);
}