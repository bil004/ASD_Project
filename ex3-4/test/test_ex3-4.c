#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/Unity/src/unity.h"
#include "../include/graph.h"
#include "../include/hash.h"

// Funzione di confronto per stringhe (case-sensitive)
static int compare_str(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

// Funzione di hash per stringhe (djb2)
static unsigned long hash_str(const void* key) {
    unsigned long hash = 5381;
    const char* str = (const char*)key;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

Graph gr;

void setUp(void) {
    printf("[DEBUG] setUp called\n");
    // Crea un grafo etichettato e non diretto per ogni test
    gr = graph_create(1, 0, compare_str, hash_str);
    printf("[DEBUG] setUp: graph_create returned %p\n", (void*)gr);
}

void tearDown(void) {
    printf("[DEBUG] tearDown called\n");
    // Libera la memoria del grafo dopo ogni test
    graph_free(gr);
    printf("[DEBUG] tearDown: graph_free done\n");
}

// Test: aggiunta e verifica presenza di un nodo
void test_graph_add_and_contains_node(void) {
    TEST_ASSERT_EQUAL(1, graph_add_node(gr, "A"));
    TEST_ASSERT_TRUE(graph_contains_node(gr, "A"));
    // Aggiunta di un nodo già presente deve restituire 0
    TEST_ASSERT_EQUAL(0, graph_add_node(gr, "A"));
}

// Test: aggiunta e verifica presenza di un arco
void test_graph_add_and_contains_edge(void) {
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    TEST_ASSERT_EQUAL(1, graph_add_edge(gr, "A", "B", "label1"));
    TEST_ASSERT_TRUE(graph_contains_edge(gr, "A", "B"));
    // Essendo non diretto, anche l'arco inverso deve esistere
    TEST_ASSERT_TRUE(graph_contains_edge(gr, "B", "A"));
}

// Test: numero di nodi e archi
void test_graph_num_nodes_and_edges(void) {
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    graph_add_node(gr, "C");
    graph_add_edge(gr, "A", "B", "l1");
    graph_add_edge(gr, "A", "C", "l2");
    TEST_ASSERT_EQUAL(3, graph_num_nodes(gr));
    TEST_ASSERT_EQUAL(2, graph_num_edges(gr));
}

// Test: recupero dei nodi e dei vicini
void test_graph_get_nodes_and_neighbours(void) {
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    graph_add_node(gr, "C");
    graph_add_edge(gr, "A", "B", "l1");
    graph_add_edge(gr, "A", "C", "l2");
    void** nodes = graph_get_nodes(gr);
    int foundA = 0, foundB = 0, foundC = 0;
    for (int i = 0; nodes[i] != NULL; i++) {
        if (strcmp(nodes[i], "A") == 0) foundA = 1;
        if (strcmp(nodes[i], "B") == 0) foundB = 1;
        if (strcmp(nodes[i], "C") == 0) foundC = 1;
    }
    TEST_ASSERT_TRUE(foundA && foundB && foundC);
    free(nodes);
    void** neigh = graph_get_neighbours(gr, "A");
    int foundB2 = 0, foundC2 = 0;
    for (int i = 0; neigh[i] != NULL; i++) {
        if (strcmp(neigh[i], "B") == 0) foundB2 = 1;
        if (strcmp(neigh[i], "C") == 0) foundC2 = 1;
    }
    TEST_ASSERT_TRUE(foundB2 && foundC2);
    free(neigh);
}

// Test: recupero dell'etichetta di un arco
void test_graph_get_label(void) {
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    graph_add_edge(gr, "A", "B", "pippo");
    void* label = graph_get_label(gr, "A", "B");
    TEST_ASSERT_NOT_NULL(label);
    TEST_ASSERT_EQUAL_STRING("pippo", (char*)label);
}

// Test: rimozione di un nodo e di un arco
void test_graph_remove_node_and_edge(void) {
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    graph_add_edge(gr, "A", "B", "l1");
    TEST_ASSERT_EQUAL(1, graph_remove_node(gr, "A"));
    TEST_ASSERT_FALSE(graph_contains_node(gr, "A"));
    TEST_ASSERT_FALSE(graph_contains_edge(gr, "A", "B"));
}

// Test: aggiunta di un arco tra nodi non esistenti
void test_graph_add_edge_nonexistent_nodes(void) {
    // Nessun nodo aggiunto
    TEST_ASSERT_EQUAL(-1, graph_add_edge(gr, "X", "Y", "label"));
}

// Test: rimozione di un arco non esistente
void test_graph_remove_nonexistent_edge(void) {
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    // Nessun arco aggiunto
    TEST_ASSERT_EQUAL(0, graph_remove_edge(gr, "A", "B"));
}

int main(void) {
    printf("[DEBUG] test_ex3-4 main started\n");
    UNITY_BEGIN();
    RUN_TEST(test_graph_add_and_contains_node);
    RUN_TEST(test_graph_add_and_contains_edge);
    RUN_TEST(test_graph_num_nodes_and_edges);
    RUN_TEST(test_graph_get_nodes_and_neighbours);
    RUN_TEST(test_graph_get_label);
    RUN_TEST(test_graph_remove_node_and_edge);
    RUN_TEST(test_graph_add_edge_nonexistent_nodes);
    RUN_TEST(test_graph_remove_nonexistent_edge);
    return UNITY_END();
}