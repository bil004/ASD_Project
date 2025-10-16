#ifndef SORT_H
#define SORT_H

#include <stdio.h>

/**
 * @param id id records
 * @param name string 
 * @param integerNum integer
 * @param floatNum float
 */
typedef struct records {
    int id;
    char name[100];
    int integerNum;
    float floatNum;
} Records;

/**
 * @brief Find the size of a file
 * @param fp file pointer
 * @return size of the file in bytes
 */
long int findSize(FILE *fp);

/**
 * @brief Sort the records on a file 
 * @param infile file to read
 * @param outfile file that contains all infile's ordered records
 * @param field describes which field to use
 * @param algo describes which algorithm to use
 */
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo);

/**
 * @brief Compare 2 generic elements
 * @param e1 first element
 * @param e2 second element
 * @return 1 if e1 > e2, -1 if e1 < e2, 0 if e1 == e2
 */
int compar(const void *e1, const void *e2);

/**
 * @brief Compare two Records by name
 * @param e1 first record
 * @param e2 second record
 * @return <0 if e1 < e2, 0 if e1 == e2, >0 if e1 > e2
 */
int compar_name(const void *e1, const void *e2);

/**
 * @brief Compare two Records by integerNum
 * @param e1 first record
 * @param e2 second record
 * @return <0 if e1 < e2, 0 if e1 == e2, >0 if e1 > e2
 */
int compar_integerNum(const void *e1, const void *e2);

/**
 * @brief Compare two Records by floatNum
 * @param e1 first record
 * @param e2 second record
 * @return <0 if e1 < e2, 0 if e1 == e2, >0 if e1 > e2
 */
int compar_floatNum(const void *e1, const void *e2);

/**
 * @brief Merge and order the array
 * @param base array
 * @param size size of every array's item 
 * @param compar function
 * @param left left array's index
 * @param mid mid array's index
 * @param right right array's index
 */
void merge(void *base, size_t size, int (*compar)(const void*, const void*), size_t left, size_t mid, size_t right);

/**
 * @brief Sort an array with Merge sort's algorithm
 * @param base array
 * @param size size of every array's item 
 * @param compar function
 * @param left left index
 * @param right right index
 */
void merge_sortR(void *base, size_t size, int (*compar)(const void*, const void*), size_t left, size_t right);

/**
 * @brief Merge_sortR's wrapper
 * @param base array
 * @param nitems array's size
 * @param size size of every array's item 
 * @param compar Comparison function
 */
void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));

/**
 * @brief q_sort's wrapper
 * @param base array
 * @param nitems array's size
 * @param size size of every array's item 
 * @param compar Comparison function
 */
void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));

/**
 * @brief Sort an array with Quick sort's algorithm
 * @param base array
 * @param low index of the array's first element
 * @param high index of the array's last element
 * @param size size of every array's item 
 * @param compar Comparison function
 */
void q_sort(void *base, int low, int high, size_t size, int (*compar)(const void*, const void*));

/**
 * @brief Partition an array for the Quick Sort algorithm
 * @param base Pointer to the base of the array to be partitioned.
 * @param low Index of the first element in the array.
 * @param high Index of the last element in the array.
 * @param size Size of each element in the array (in bytes).
 * @param compar Comparison function
 * 
 * @return The index of the pivot element after partitioning.
 */
int partition(void *base, int low, int high, size_t size, int (*compar)(const void*, const void*));


/**
 * @brief Selects the median of three elements (first, middle, last) in the array
 *        and rearranges them to aid in partitioning for the Quick Sort algorithm.
 *        (Used to improve the performance of Quick Sort by choosing a better pivot element)
 * 
 * @param base Pointer to the base of the array to be partitioned.
 * @param low Index of the first element in the array.
 * @param high Index of the last element in the array.
 * @param size Size of each element in the array (in bytes).
 * @param compar Comparison function
 * 
 * @return The index of the pivot element after rearranging the first, middle, 
 *         and last elements.
 */
int median_of_three(void *base, int low, int high, size_t size, int (*compar)(const void*, const void*));

/**
 * @brief Swap two elements in an array
 * @param a pointer first array
 * @param b pointer second array
 * @param size size of every array's item 
 * @param compar Comparison function
 */
void swap(void *a, void *b, size_t size);

#endif