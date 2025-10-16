#ifndef EDIT_H
#define EDIT_H

/**
 * @brief Struttura per salvare le parole del dizionario
 * @param words Array di puntatori a parole
 * @param count Numero di parole
 */
typedef struct {
    char **words;
    int count;
} Dictionary;

/**
 * @brief Find the size of a file
 * @param fp file pointer
 * @return size of the file in bytes
 */
long int findSize(FILE *fp);

/**
 * @brief Corregge il file
 * @param dictionary file di riferimento per correggere correctme
 * @param correctme file da correggere
 */
void correctFile(FILE *dictionary, FILE *correctme);

/**
 * @brief Rimuovi i segni di punteggiatura
 * @param line stringa
 */
void deletePunct(char *line);

/**
 * @brief Stabilisce la distanza tra 2 stringhe
 * @param s1 char* result
 * @param s2 char* start
 * @return numero di operazioni eseguite
 */
int edit_distance(const char *s1, const char* s2);

/**
 * @brief Stabilisce la distanza tra 2 stringhe (in modo dinamico)
 * @param s1 char* result
 * @param s2 char* start
 * @return numero di operazioni eseguite
 */
int edit_distance_dyn(const char *s1, const char* s2);

/**
 * @brief Stabilisce la distanza tra 2 stringhe usando la matrice
 * @param s1 char* result
 * @param s2 char* start
 * @param mat int** array 2D
 * @param l1 int s1 size
 * @param l2 int s2 size
 * @return numero di operazioni eseguite
 */
int edit_distance_dynA(const char *s1, const char* s2, int **mat, int l1, int l2);

#endif