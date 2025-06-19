/*************************************************
 *File----------test.c
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Tuesday Jun 17, 2025 09:01:49 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "test.h"
#include <stdio.h>
#include <string.h>

static const char *SHADER_PATH = "assets/shaders/";
static const char *VERTEX_NAME = "Vert.glsl";

int main(int argc, char *argv[]) {
        printf("Hello, World!\n");

        const char *shaderName = "cell";

        char vertexPath[40];
        strncat(vertexPath, SHADER_PATH, sizeof(vertexPath) - 1);
        strncat(vertexPath, shaderName, sizeof(vertexPath) - 1);
        strncat(vertexPath, VERTEX_NAME, sizeof(vertexPath) - 1);
        printf("%s", vertexPath);

        printf("\n");
        return 0;
}

