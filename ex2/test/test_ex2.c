#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/edit.h"
#include "../lib/Unity/src/unity.h"

void setUp() {

}

void tearDown() {

}

void test_edit_distance() {
    char *s1 = NULL, *s2 = NULL;
    TEST_ASSERT_EQUAL_INT(edit_distance(s1, s2), -1);

    s1 = "Sasso\0";
    s2 = "Masso\0";
    TEST_ASSERT_EQUAL_INT(edit_distance(s1, s2), 2);

    s1 = "";
    s2 = "";
    TEST_ASSERT_EQUAL_INT(edit_distance(s1, s2), 0);

    s1 = "abc";
    s2 = "";
    TEST_ASSERT_EQUAL_INT(edit_distance(s1, s2), 3);

    s1 = "";
    s2 = "abc";
    TEST_ASSERT_EQUAL_INT(edit_distance(s1, s2), 3);

    s1 = "flaw";
    s2 = "lawn";
    TEST_ASSERT_EQUAL_INT(edit_distance(s1, s2), 2);
}

void test_edit_distance_dyn() {
    char *s1 = NULL, *s2 = NULL;
    TEST_ASSERT_EQUAL_INT(edit_distance_dyn(s1, s2), -1);

    s1 = "Sasso\0";
    s2 = "Masso\0";
    TEST_ASSERT_EQUAL_INT(edit_distance_dyn(s1, s2), 2);

    s1 = "";
    s2 = "";
    TEST_ASSERT_EQUAL_INT(edit_distance_dyn(s1, s2), 0);

    s1 = "abc";
    s2 = "";
    TEST_ASSERT_EQUAL_INT(edit_distance_dyn(s1, s2), 3);

    s1 = "";
    s2 = "abc";
    TEST_ASSERT_EQUAL_INT(edit_distance_dyn(s1, s2), 3);

    s1 = "flaw";
    s2 = "lawn";
    TEST_ASSERT_EQUAL_INT(edit_distance_dyn(s1, s2), 2);
}

void test_correctFile() {
    FILE *d = fopen("../files/temp_dictionary.txt", "w");
    FILE *c = fopen("../files/temp_correctme.txt", "w");

    TEST_ASSERT_NOT_NULL(d);
    TEST_ASSERT_NOT_NULL(c);

    fprintf(d, "casa\ncara\nvino\npassato\npioppo\n");
    fprintf(c, "casa\ntassa\nvinaio\noppio\n");

    fclose(d);
    fclose(c);

    d = fopen("../files/temp_dictionary.txt", "r");
    c = fopen("../files/temp_correctme.txt", "r+");
    TEST_ASSERT_NOT_NULL(d);
    TEST_ASSERT_NOT_NULL(c);

    correctFile(d, c);

    rewind(c);
    char buf[256];

    fgets(buf, sizeof(buf), c);
    TEST_ASSERT_EQUAL_STRING("casa\n", buf);

    fgets(buf, sizeof(buf), c);
    TEST_ASSERT_EQUAL_STRING("tassa\n", buf);

    fclose(d);
    fclose(c);
    remove("../files/temp_dictionary.txt");
    remove("../files/temp_correctme.txt");
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_edit_distance);
    RUN_TEST(test_edit_distance_dyn);
    RUN_TEST(test_correctFile);
    return UNITY_END();
}