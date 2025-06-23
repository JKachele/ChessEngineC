/*************************************************
 *File----------render.h
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 12, 2025 13:06:21 EDT
 *License-------GNU GPL-3.0
 ************************************************/
#ifndef RENDER_H
#define RENDER_H

#include "gfx.h"
#include "shader.h"
#include "camera.h"
#include "../enttiy/board.h"
#include "../enttiy/piece.h"

struct Renderer {
        struct Camera camera;

        struct Board board;

        struct Piece piece;
};

void renderInit(struct Renderer *self);
void renderUpdate(struct Renderer *self, ivec2s windowSize);
void renderEntities(struct Renderer *self, struct Positions *positions);
void renderDestroy(struct Renderer *self);

#endif

