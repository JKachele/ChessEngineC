/*************************************************
 *File----------test.c
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Tuesday Jun 17, 2025 09:01:49 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
        printf("Hello, World!\n");

        for (int i = 0; i < 20; i++) {
                float ranX = (float)rand() / (float)(RAND_MAX/0.75);
                float ranY = (float)rand() / (float)(RAND_MAX/0.75);
                printf("%f, %f\n", ranX, ranY);
        }

        printf("\n");
        return 0;
}

