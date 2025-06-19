/*************************************************
 *File----------shader.c
 *Project-------ChessEngine
 *Author--------Justin Kachele
 *Created-------Tuesday Jan 21, 2025 09:48:59 EST
 *License-------GNU GPL-3.0
 ************************************************/

#include "shader.h"
#include <string.h>

static const char *SHADER_PATH = "assets/shaders/";
static const char *VERTEX_NAME = "Vert.glsl";
static const char *FRAGMENT_NAME = "Frag.glsl";

static unsigned int _compile(const char *path, GLenum type) {
        FILE *f;
        char *shaderSource;
        long len;

        f = fopen(path, "rb");
        if (f == NULL) {
                fprintf(stderr, "Error loading shader at %s\n", path);
                exit(1);
        }

        fseek(f, 0, SEEK_END);
        len = ftell(f);
        assert(len > 0);
        fseek(f, 0, SEEK_SET);
        shaderSource = calloc(1, len);
        assert(shaderSource != NULL);
        fread(shaderSource, 1, len, f);
        assert(strlen(shaderSource) > 0);
        fclose(f);

        unsigned int shaderHandle = glCreateShader(type);
        glShaderSource(shaderHandle, 1, (const GLchar**) &shaderSource,
                        (const GLint*)&len);
        glCompileShader(shaderHandle);

        int success;
        char infoLog[512];
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
        if (!success) {
                glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);
                if (type == GL_VERTEX_SHADER)
                        printf("ERROR: SHADER VERTEX COMPILATION FAILED\n%s\n",
                                infoLog);
                if (type == GL_FRAGMENT_SHADER)
                        printf("ERROR: SHADER FRAGMENT COMPILATION FAILED\n"
                                        "%s\n", infoLog);
                else
                        printf("ERROR: SHADER COMPILATION FAILED\n%s\n",
                                infoLog);
        }

        free(shaderSource);
        return shaderHandle;
}

void shaderInit(struct Shader *self, const char* shadername) {
        const int PathSize = 40;
        char vertexPath[PathSize];
        snprintf(vertexPath, PathSize, "%s%s%s",
                        SHADER_PATH, shadername, VERTEX_NAME);
        GLuint vertexShader = _compile(vertexPath, GL_VERTEX_SHADER);

        char fragmentPath[PathSize];
        snprintf(fragmentPath, PathSize, "%s%s%s",
                        SHADER_PATH, shadername, FRAGMENT_NAME);
        GLuint fragmentShader = _compile(fragmentPath, GL_FRAGMENT_SHADER);

        GLuint shader = glCreateProgram();
        glAttachShader(shader, vertexShader);
        glAttachShader(shader, fragmentShader);
        glLinkProgram(shader);

        int success;
        char infoLog[512];
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
                glGetProgramInfoLog(shader, 512, NULL, infoLog);
                printf("ERROR: SHADER LINKING FAILED\n%s\n",
                                infoLog);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        self->handle = shader;
        glUseProgram(self->handle);
}

void shaderUse(struct Shader *self) {
        glUseProgram(self->handle);
}

void shaderDestroy(struct Shader *self) {
        glDeleteProgram(self->handle);
}

