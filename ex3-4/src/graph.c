#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/hash.h"
#include "../include/graph.h"

Graph graph_create(int labelled, int directed, int (*compare)(const void *, const void *), unsigned long (*hash)(const void *)) {
    Graph g = malloc(sizeof(*g)); 
    if (g == NULL) return NULL;

    g->adjacentList = hash_table_create(compare, hash); // Usa i parametri passati
    if (g->adjacentList == NULL) {
        free(g);
        return NULL;
    }

    g->directed = directed;
    g->labeled = labelled;

    return g;
}

int graph_is_directed(const Graph gr) {
    return gr->directed;
}

int graph_is_labelled(const Graph gr) {
    return gr->labeled;
}

int graph_add_node(Graph gr, const void *node) {
    if (gr == NULL || node == NULL) 
        return -1;
    
    if (hash_table_contains_key(gr->adjacentList, node)) 
        return 0;

    // Inizializza la lista di adiacenza come array vuoto terminato da NULL
    Edge **empty_list = malloc(sizeof(Edge*));
    empty_list[0] = NULL;
    hash_table_put(gr->adjacentList, node, empty_list);
    
    return 1;
}


int add_edge_to_list(Graph gr, const void *source, const void *dest, const void *label) {
    Edge **adj_list = hash_table_get(gr->adjacentList, source);
    size_t size = 0;

    // Calcola la dimensione della lista di adiacenza
    if (adj_list) {
        while (adj_list[size] != NULL) size++;
    }

    // Alloca memoria per il nuovo arco
    Edge **new_list = realloc(adj_list, (size + 2) * sizeof(Edge*));
    if (new_list == NULL) {
        perror("Memory allocation failed");
        return -1;
    }

    Edge *new_edge = malloc(sizeof(Edge));
    if (new_edge == NULL) {
        perror("Memory allocation failed");
        return -1;
    }
    new_edge->source = (void*)source;
    new_edge->dest = (void*)dest;
    new_edge->label = (void*)label;

    new_list[size] = new_edge;
    new_list[size + 1] = NULL; // Termina la lista con NULL
    hash_table_put(gr->adjacentList, source, new_list);

    return 1;
}

int graph_add_edge(Graph gr, const void *node1, const void *node2, const void *label) {
    if (gr == NULL || node1 == NULL || node2 == NULL || label == NULL)
        return -1; // Parametri non validi

    // Controlla se i nodi esistono
    if (!hash_table_contains_key(gr->adjacentList, node1) || 
        !hash_table_contains_key(gr->adjacentList, node2)) {
        return -1; // Uno dei nodi non esiste
    }

    if (add_edge_to_list(gr, node1, node2, label) == -1) return -1;

    if (!gr->directed) {
        if (add_edge_to_list(gr, node2, node1, label) == -1) return -1;
    }

    return 1; // Arco aggiunto con successo
}

int graph_contains_node(const Graph gr, const void *node) {
    return hash_table_contains_key(gr->adjacentList, node);
}

int graph_contains_edge(const Graph gr, const void *node1, const void *node2) {
    if (gr == NULL)
        return -1;
    
    return hash_table_contains_key(gr->adjacentList, node1) && hash_table_contains_key(gr->adjacentList, node2);
}     

int graph_num_nodes(const Graph gr) {
    if (gr == NULL) 
        return -1; 

    return hash_table_size(gr->adjacentList);
}

int graph_num_edges(const Graph gr) {
    if (gr == NULL) return -1;
    int num_edges = 0;
    void **nodes = graph_get_nodes(gr);
    if (!nodes) return 0;
    for (int i = 0; nodes[i] != NULL; i++) {
        Edge **edges = (Edge **)hash_table_get(gr->adjacentList, nodes[i]);
        if (edges) {
            for (int j = 0; edges[j] != NULL; j++) {
                num_edges++;
            }
        }
    }
    free(nodes);
    if (!gr->directed) num_edges /= 2;
    return num_edges;
}

void **graph_get_nodes(const Graph gr) {
    if (gr == NULL) return NULL;
    return hash_table_keyset(gr->adjacentList);
}

Edge **graph_get_edges(const Graph gr) {
    if (gr == NULL) return NULL;
    int total = graph_num_edges(gr);
    if (total <= 0) return NULL;
    Edge **edges = malloc((total + 1) * sizeof(Edge*));
    int idx = 0;
    void **nodes = graph_get_nodes(gr);
    if (!nodes) return NULL;
    for (int i = 0; nodes[i] != NULL; i++) {
        Edge **adj = (Edge **)hash_table_get(gr->adjacentList, nodes[i]);
        if (adj) {
            for (int j = 0; adj[j] != NULL; j++) {
                if (gr->directed || (void*)adj[j]->source <= (void*)adj[j]->dest) {
                    edges[idx++] = adj[j];
                }
            }
        }
    }
    edges[idx] = NULL;
    free(nodes);
    return edges;
}

void **graph_get_neighbours(const Graph gr, const void *node) {
    if (gr == NULL || node == NULL) return NULL;
    Edge **adj = (Edge **)hash_table_get(gr->adjacentList, node);
    if (!adj) {
        return NULL;
    }
    int count = 0;
    while (adj[count] != NULL) count++;
    void **neigh = malloc((count + 1) * sizeof(void*));
    for (int i = 0; i < count; i++) {
        neigh[i] = adj[i]->dest;
    }
    neigh[count] = NULL;
    return neigh;
}

int graph_num_neighbours(const Graph gr, const void *node) {
    if (gr == NULL || node == NULL) return -1;
    Edge **adj = (Edge **)hash_table_get(gr->adjacentList, node);
    if (!adj) return 0;
    int count = 0;
    while (adj[count] != NULL) count++;
    return count;
}

void *graph_get_label(const Graph gr, const void *node1, const void *node2) {
    if (gr == NULL || node1 == NULL || node2 == NULL) return NULL;
    Edge **adj = (Edge **)hash_table_get(gr->adjacentList, node1);
    if (!adj) return NULL;
    for (int i = 0; adj[i] != NULL; i++) {
        if (gr->adjacentList->compare(adj[i]->dest, node2) == 0) {
            return adj[i]->label;
        }
    }
    return NULL;
}

void graph_free(Graph gr) {
    if (gr == NULL) return;
    void **nodes = graph_get_nodes(gr);
    if (nodes) {
        for (int i = 0; nodes[i] != NULL; i++) {
            Edge **adj = (Edge **)hash_table_get(gr->adjacentList, nodes[i]);
            if (adj) {
                for (int j = 0; adj[j] != NULL; j++) {
                    free(adj[j]);
                }
                free(adj);
            }
        }
        free(nodes);
    }
    hash_table_free(gr->adjacentList);
    free(gr);
}

// Rimuove un nodo dal grafo e tutti gli archi associati
int graph_remove_node(Graph gr, const void *node) {
    if (gr == NULL || node == NULL) return -1;
    if (!hash_table_contains_key(gr->adjacentList, node)) return 0;
    // Rimuovi tutti gli archi entranti verso node
    void **nodes = graph_get_nodes(gr);
    if (nodes) {
        for (int i = 0; nodes[i] != NULL; i++) {
            if (gr->adjacentList->compare(nodes[i], node) == 0) continue;
            Edge **adj = (Edge **)hash_table_get(gr->adjacentList, nodes[i]);
            if (adj) {
                int count = 0, found = 0;
                while (adj[count] != NULL) count++;
                int new_count = 0;
                Edge **new_adj = malloc((count + 1) * sizeof(Edge*));
                for (int j = 0; j < count; j++) {
                    if (gr->adjacentList->compare(adj[j]->dest, node) == 0) {
                        free(adj[j]);
                        found = 1;
                    } else {
                        new_adj[new_count++] = adj[j];
                    }
                }
                new_adj[new_count] = NULL;
                if (found) {
                    free(adj);
                    hash_table_put(gr->adjacentList, nodes[i], new_adj);
                } else {
                    free(new_adj);
                }
            }
        }
        free(nodes);
    }
    // Rimuovi tutti gli archi uscenti da node
    Edge **adj = (Edge **)hash_table_get(gr->adjacentList, node);
    if (adj) {
        for (int j = 0; adj[j] != NULL; j++) {
            free(adj[j]);
        }
        free(adj);
    }
    hash_table_remove(gr->adjacentList, node);
    return 1;
}

// Rimuove un arco dal grafo
int graph_remove_edge(Graph gr, const void *node1, const void *node2) {
    if (gr == NULL || node1 == NULL || node2 == NULL) return -1;
    if (!hash_table_contains_key(gr->adjacentList, node1) || !hash_table_contains_key(gr->adjacentList, node2)) return 0;
    int removed = 0;
    // Rimuovi da node1 -> node2
    Edge **adj = (Edge **)hash_table_get(gr->adjacentList, node1);
    if (adj) {
        int count = 0, found = 0;
        while (adj[count] != NULL) count++;
        int new_count = 0;
        Edge **new_adj = malloc((count + 1) * sizeof(Edge*));
        for (int j = 0; j < count; j++) {
            if (gr->adjacentList->compare(adj[j]->dest, node2) == 0) {
                free(adj[j]);
                found = 1;
            } else {
                new_adj[new_count++] = adj[j];
            }
        }
        new_adj[new_count] = NULL;
        if (found) {
            free(adj);
            hash_table_put(gr->adjacentList, node1, new_adj);
            removed = 1;
        } else {
            free(new_adj);
        }
    }
    // Se non diretto, rimuovi anche da node2 -> node1
    if (!gr->directed) {
        Edge **adj2 = (Edge **)hash_table_get(gr->adjacentList, node2);
        if (adj2) {
            int count2 = 0, found2 = 0;
            while (adj2[count2] != NULL) count2++;
            int new_count2 = 0;
            Edge **new_adj2 = malloc((count2 + 1) * sizeof(Edge*));
            for (int j = 0; j < count2; j++) {
                if (gr->adjacentList->compare(adj2[j]->dest, node1) == 0) {
                    free(adj2[j]);
                    found2 = 1;
                } else {
                    new_adj2[new_count2++] = adj2[j];
                }
            }
            new_adj2[new_count2] = NULL;
            if (found2) {
                free(adj2);
                hash_table_put(gr->adjacentList, node2, new_adj2);
                removed = 1;
            } else {
                free(new_adj2);
            }
        }
    }
    return removed;
}