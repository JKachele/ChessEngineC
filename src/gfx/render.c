/*************************************************
 *File----------render.c
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 12, 2025 13:06:45 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "render.h"

void renderInit(struct Renderer *self) {
        *self = (struct Renderer) {0};

        boardInit(&self->board);
        pieceInit(&self->piece);

        cameraInit(&self->camera);
}

void createTransformations(struct Renderer *self) {
        struct Camera *cam = &self->camera;
        mat4s view = cam->getView(cam);
        mat4s projection = cam->getProjection(cam);
        
        boardLoadTransforms(&self->board, view, projection);
        pieceLoadTransforms(&self->piece, view, projection);
}

void renderUpdate(struct Renderer *self, ivec2s windowSize) {
        cameraResize(&self->camera, windowSize);
        createTransformations(self);
}

void renderEntities(struct Renderer *self, struct Positions *positions) {
        renderBoard(&self->board);
        renderPieces(&self->piece, positions);
}

void renderDestroy(struct Renderer *self) {
        boardDelete(&self->board);
        pieceDelete(&self->piece);
}

