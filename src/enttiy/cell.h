/*************************************************
 *File----------cell.h
 *Project-------ChessEngineC
 *Author--------Justin Kachele
 *Created-------Wednesday Jun 18, 2025 17:08:04 EDT
 *License-------GNU GPL-3.0
 ************************************************/
#ifndef CELL_H
#define CELL_H

#include "../gfx/gfx.h"

struct Cell {
        int id;
        int pieceID;

        GLuint vao;
        GLuint vbo;
        GLuint ebo;
};

void cellInit(struct Cell *self, int id);
void renderCell(struct Cell *self, GLuint shaderHandler);
void cellDelete(struct Cell *self);

#endif

