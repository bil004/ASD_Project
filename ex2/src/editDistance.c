#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/edit.h"

int edit_distance(const char *s1, const char* s2) {
    if (s1 == NULL || s2 == NULL) return -1;
      
    if (*s1 == '\0') return strlen(s2);
    if (*s2 == '\0') return strlen(s1);
    
    if (*s1 == *s2) return edit_distance(s1 + 1, s2 + 1);

    int insert_cost = edit_distance(s1, s2 + 1);      
    int delete_cost = edit_distance(s1 + 1, s2);
    
    return 1 + (insert_cost < delete_cost ? insert_cost : delete_cost);
}

int edit_distance_dynA(const char *s1, const char* s2, int **mat, int l1, int l2) {
    if (s1 == NULL || s2 == NULL) return -1;
    
    if (l1 == 0) return l2;
    if (l2 == 0) return l1;

    if (mat[l1][l2] != -1) 
        return mat[l1][l2];

    if (s1[l1 - 1] == s2[l2 - 1])
        mat[l1][l2] = edit_distance_dynA(s1, s2, mat, l1 - 1, l2 - 1);
    else {
        int insert_cost = edit_distance_dynA(s1, s2, mat, l1, l2 - 1);
        int delete_cost = edit_distance_dynA(s1, s2, mat, l1 - 1, l2);
        mat[l1][l2] = 1 + (insert_cost < delete_cost ? insert_cost : delete_cost);
    }

    return mat[l1][l2];
}

int edit_distance_dyn(const char *s1, const char* s2) {
    if (s1 == NULL || s2 == NULL) return -1;

    int l1 = strlen(s1), l2 = strlen(s2);

    int **res = malloc((l1 + 1) * sizeof(int *));
    if (res == NULL) return -1;


    for (int i = 0; i <= l1; i++) {
        res[i] = malloc((l2 + 1) * sizeof(int));
        if (res[i] == NULL) {
            for (int j = 0; j < i; j++) free(res[j]);
            free(res);
            return -1;
        }
        
        for (int j = 0; j <= l2; j++) 
            res[i][j] = -1;
    }

    int result = edit_distance_dynA(s1, s2, res, l1, l2);

    for (int i = 0; i <= l1; i++) 
        free(res[i]);

    free(res);

    return result;
}