#ifndef GRAPH_H
#define GRAPH_H

#include "../include/hash.h"

/**
 * @struct graph
 * @brief Structure representing a graph with an adjacency list, direction, and label information.
 */
typedef struct graph {
    HashTable* adjacentList; /**< Hash table representing adjacency lists for each node. */
    int directed;           /**< 1 if the graph is directed, 0 otherwise. */
    int labeled;            /**< 1 if the graph is labeled, 0 otherwise. */
}*Graph;

/**
 * @struct edge
 * @brief Structure representing an edge in the graph.
 */
typedef struct edge {
    void *source; /**< Source node of the edge. */
    void *dest;   /**< Destination node of the edge. */
    void *label;  /**< Label of the edge (can be NULL if unlabeled). */
} Edge;

/**
 * @brief Creates an empty graph.
 * @param labelled 1 if the graph is labeled, 0 otherwise.
 * @param directed 1 if the graph is directed, 0 otherwise.
 * @param compare Function to compare nodes.
 * @param hash Function to hash nodes.
 * @return Pointer to the created graph.
 */
Graph graph_create(int labelled, int directed,
                   int (*compare)(const void *, const void *),
                   unsigned long (*hash)(const void *));

/**
 * @brief Checks if the graph is directed.
 * @param gr Pointer to the graph.
 * @return 1 if directed, 0 otherwise.
 */
int graph_is_directed(const Graph gr);

/**
 * @brief Checks if the graph is labeled.
 * @param gr Pointer to the graph.
 * @return 1 if labeled, 0 otherwise.
 */
int graph_is_labelled(const Graph gr);

/**
 * @brief Adds a node to the graph.
 * @param gr Pointer to the graph.
 * @param node Pointer to the node to add.
 * @return 1 if added, 0 if already present, -1 on error.
 */
int graph_add_node(Graph gr, const void *node);

/**
 * @brief Adds an edge to the graph.
 * @param gr Pointer to the graph.
 * @param node1 Source node.
 * @param node2 Destination node.
 * @param label Edge label (can be NULL).
 * @return 1 if added, -1 on error.
 */
int graph_add_edge(Graph gr, const void *node1, const void *node2, const void *label);

/**
 * @brief Checks if a node exists in the graph.
 * @param gr Pointer to the graph.
 * @param node Pointer to the node.
 * @return 1 if present, 0 otherwise.
 */
int graph_contains_node(const Graph gr, const void *node);

/**
 * @brief Checks if an edge exists in the graph.
 * @param gr Pointer to the graph.
 * @param node1 Source node.
 * @param node2 Destination node.
 * @return 1 if present, 0 otherwise.
 */
int graph_contains_edge(const Graph gr, const void *node1, const void *node2);

/**
 * @brief Removes a node and all its edges from the graph.
 * @param gr Pointer to the graph.
 * @param node Pointer to the node to remove.
 * @return 1 if removed, 0 if not present, -1 on error.
 */
int graph_remove_node(Graph gr, const void *node);

/**
 * @brief Removes an edge from the graph.
 * @param gr Pointer to the graph.
 * @param node1 Source node.
 * @param node2 Destination node.
 * @return 1 if removed, 0 if not present, -1 on error.
 */
int graph_remove_edge(Graph gr, const void *node1, const void *node2);

/**
 * @brief Returns the number of nodes in the graph.
 * @param gr Pointer to the graph.
 * @return Number of nodes, or -1 on error.
 */
int graph_num_nodes(const Graph gr);

/**
 * @brief Returns the number of edges in the graph.
 * @param gr Pointer to the graph.
 * @return Number of edges, or -1 on error.
 */
int graph_num_edges(const Graph gr);

/**
 * @brief Returns an array of all nodes in the graph (NULL-terminated).
 * @param gr Pointer to the graph.
 * @return Array of node pointers, or NULL on error. Must be freed by the caller.
 */
void **graph_get_nodes(const Graph gr);

/**
 * @brief Returns an array of all edges in the graph (NULL-terminated).
 * @param gr Pointer to the graph.
 * @return Array of edge pointers, or NULL on error. Must be freed by the caller.
 */
Edge **graph_get_edges(const Graph gr);

/**
 * @brief Returns an array of neighbours for a given node (NULL-terminated).
 * @param gr Pointer to the graph.
 * @param node Pointer to the node.
 * @return Array of neighbour node pointers, or NULL on error. Must be freed by the caller.
 */
void **graph_get_neighbours(const Graph gr, const void *node);

/**
 * @brief Returns the number of neighbours for a given node.
 * @param gr Pointer to the graph.
 * @param node Pointer to the node.
 * @return Number of neighbours, or -1 on error.
 */
int graph_num_neighbours(const Graph gr, const void *node);

/**
 * @brief Returns the label of the edge between two nodes.
 * @param gr Pointer to the graph.
 * @param node1 Source node.
 * @param node2 Destination node.
 * @return Pointer to the label, or NULL if not present.
 */
void *graph_get_label(const Graph gr, const void *node1, const void *node2);

/**
 * @brief Frees all memory associated with the graph.
 * @param gr Pointer to the graph.
 */
void graph_free(Graph gr);

/**
 * @brief Performs a breadth-first visit starting from a node.
 * @param gr Pointer to the graph.
 * @param start Pointer to the starting node.
 * @param compare Function to compare nodes.
 * @param hash Function to hash nodes.
 * @return Array of node pointers in visit order (NULL-terminated), or NULL if start not present. Must be freed by the caller.
 */
void** breadth_first_visit(Graph gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*));

/**
 * @brief Performs a breadth-first search on a graph loaded from a file.
 * @param src File pointer to the source file containing the graph.
 * @param city Name of the starting node.
 * @param result File pointer to the file where the result will be written.
 */
void bsf(FILE *src, const char *city, FILE *result);


#endif