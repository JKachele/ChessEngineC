/*************************************************
 *File----------piece.h
 *Project-------ChessEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 19, 2025 12:41:37 EDT
 *License-------GNU GPL-3.0
 ************************************************/
#ifndef PIECE_H
#define PIECE_H

#include "../gfx/gfx.h"
#include "../gfx/texture.h"
#include "../gfx/shader.h"
#include "../game/positions.h"

struct Piece {
        GLuint vao;
        GLuint vbo;
        GLuint ebo;

        struct Texture pieceAtlas;
        struct Shader shader;
};

void pieceInit(struct Piece *self);
void pieceLoadTransforms(struct Piece *self, mat4s view, mat4s projection);
void renderPieces(struct Piece *self, struct Positions *positions);
void pieceDelete(struct Piece *self);

#endif

