/*************************************************
 *File----------board.h
 *Project-------ChessEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 19, 2025 13:33:41 EDT
 *License-------GNU GPL-3.0
 ************************************************/
#ifndef BOARD_H
#define BOARD_H

#include "../gfx/gfx.h"
#include "../gfx/texture.h"
#include "../gfx/shader.h"

struct Cell {
        int id;

        vec2s texOffset;

        GLuint vao;
        GLuint vbo;
        GLuint ebo;
};

struct Board {
        struct Cell cells[64];
        struct Texture oakTexture;
        struct Texture walnutTexture;

        struct Shader shader;
};

void boardInit(struct Board *self);
void boardLoadTransforms(struct Board *self, mat4s view, mat4s projection);
void renderBoard(struct Board *self);
void boardDelete(struct Board *self);

#endif

