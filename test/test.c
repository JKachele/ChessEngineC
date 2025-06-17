/*************************************************
 *File----------test.c
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Tuesday Jun 17, 2025 09:01:49 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "test.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Hello, World!\n");

    struct test test;
    test.arr[5] = 100;
    test.arr2[5] = 200;
    printf("%d, %d\n", test.arr[5], test.arr2[5]);

    return 0;
}

