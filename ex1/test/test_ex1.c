#include <stdlib.h>
#include <string.h>

#include "../include/sort.h"
#include "../lib/Unity/src/unity.h"

void setUp() {
    
}

void tearDown() {
    
}

void test_array_empty() {
    char *a = NULL;
    int *b = NULL;

    merge_sort(a, 0, sizeof(char), NULL);
    TEST_ASSERT_NULL(a);
    quick_sort(b, 0, sizeof(int), NULL);
    TEST_ASSERT_NULL(b);
}

void test_array_equals() {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {5, 4, 3, 2, 1};

    merge_sort(a, 5, sizeof(int), compar);
    quick_sort(b, 5, sizeof(int), compar);

    for (size_t i = 0; i < 5; i++)
        TEST_ASSERT_EQUAL(a[i], b[i]);
}

void test_array_not_equals() {
    char a[] = {'1', '2', '3', '4', '5'};
    int b[] = {5, 4, 8, 2, 1};

    merge_sort(a, 5, sizeof(char), compar);
    quick_sort(b, 5, sizeof(int), compar);

    for (size_t i = 0; i < 5; i++)
        TEST_ASSERT_NOT_EQUAL(a[i], b[i]);
}

void test_swap_empty_elements() {
    char a = '5';
    float b = 9.0f;
    char temp = a;

    swap(&a, &b, sizeof(char));
    TEST_ASSERT_NOT_EQUAL(a, temp);
}

void test_swap() {
    int a = 5, b = 10;
    swap(&a, &b, sizeof(int));
    TEST_ASSERT_EQUAL(10, a);
    TEST_ASSERT_EQUAL(5, b);
}

void test_partition() {
    int arr[] = {9, 3, 7, 6, 2, 8};
    int size = 6;
    int pivot = partition(arr, 0, size - 1, sizeof(int), compar);

    for (int i = 0; i <= pivot; i++)
        TEST_ASSERT_LESS_OR_EQUAL(arr[i], arr[pivot]);

    for (int i = pivot + 1; i < size; i++)
        TEST_ASSERT_GREATER_THAN(arr[pivot], arr[i]);
}

void test_quick_sort_order() {
    int arr[] = {9, 3, 7, 6, 2, 8};
    int sorted[] = {2, 3, 6, 7, 8, 9};

    quick_sort(arr, 6, sizeof(int), compar);
    for (int i = 0; i < 6; i++)
        TEST_ASSERT_EQUAL(sorted[i], arr[i]);
}

void test_merge_sort_order() {
    int arr[] = {9, 3, 7, 6, 2, 8};
    int sorted[] = {2, 3, 6, 7, 8, 9};
    int size = 6;

    merge_sort(arr, size, sizeof(int), compar);
    for (int i = 0; i < size; i++)
        TEST_ASSERT_EQUAL(sorted[i], arr[i]);
}

void test_sort_records() {
    FILE *infile = fopen("../files/test_input.csv", "w+");
    FILE *outfile = fopen("../files/test_output.csv", "w+");
    TEST_ASSERT_NOT_NULL(infile);
    TEST_ASSERT_NOT_NULL(outfile);

    fprintf(infile, "3,John,25,3.5\n");
    fprintf(infile, "1,Alice,30,2.1\n");
    fprintf(infile, "2,Bob,20,4.7\n");
    rewind(infile);

    sort_records(infile, outfile, 1, 1);

    outfile = fopen("../files/test_output.csv", "r");

    char line[400];
    if (fgets(line, sizeof(line), outfile) != NULL) 
        TEST_ASSERT_EQUAL_STRING_LEN("1,Alice,30,2.10\n", line, 15);

    if (fgets(line, sizeof(line), outfile) != NULL) 
        TEST_ASSERT_EQUAL_STRING_LEN("2,Bob,20,4.70\n", line, 14);

    if (fgets(line, sizeof(line), outfile) != NULL) 
        TEST_ASSERT_EQUAL_STRING_LEN("3,John,25,3.50\n", line, 15);

    
    fclose(outfile);
    remove("../files/test_input.csv");
    remove("../files/test_output.csv");

}

void test_merge_sort_function() {
    Records arr[] = {
        {1, "John", 25, 3.5},
        {2, "Alice", 30, 2.1},
        {3, "Bob", 20, 4.7}
    };
    size_t size = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, size, sizeof(Records), compar_name);
    TEST_ASSERT_EQUAL_STRING("Alice", arr[0].name);
    TEST_ASSERT_EQUAL_STRING("Bob", arr[1].name);
    TEST_ASSERT_EQUAL_STRING("John", arr[2].name);
}

void test_quick_sort_function() {
    Records arr[] = {
        {1, "John", 25, 3.5},
        {2, "Alice", 30, 2.1},
        {3, "Bob", 20, 4.7}
    };
    size_t size = sizeof(arr) / sizeof(arr[0]);

    quick_sort(arr, size, sizeof(Records), compar_integerNum);
    TEST_ASSERT_EQUAL(20, arr[0].integerNum);
    TEST_ASSERT_EQUAL(25, arr[1].integerNum);
    TEST_ASSERT_EQUAL(30, arr[2].integerNum);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_array_empty);
    RUN_TEST(test_array_equals);
    RUN_TEST(test_array_not_equals);
    RUN_TEST(test_swap_empty_elements);
    RUN_TEST(test_swap);
    RUN_TEST(test_partition);
    RUN_TEST(test_quick_sort_order);
    RUN_TEST(test_merge_sort_order);
    RUN_TEST(test_sort_records);
    RUN_TEST(test_merge_sort_function);
    RUN_TEST(test_quick_sort_function);
    return UNITY_END();
}