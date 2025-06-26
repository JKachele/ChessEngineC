/*************************************************
 *File----------render.c
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 12, 2025 13:06:45 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "render.h"
#include "../state.h"
#include "cglm/struct/vec2.h"

void renderInit(struct Renderer *self) {
        *self = (struct Renderer) {0};

        boardInit(&self->board);
        pieceInit(&self->piece);

        cameraInit(&self->camera);

        self->mousePos = (vec2s){{0, 0}};
}

static void _createTransformations(struct Renderer *self) {
        struct Camera *cam = &self->camera;
        mat4s view = cam->getView(cam);
        mat4s projection = cam->getProjection(cam);
        
        boardLoadTransforms(&self->board, view, projection);
        pieceLoadTransforms(&self->piece, view, projection);
}

static void _getMousePos(struct Renderer *self, ivec2s winSize, vec2s mousePos) {
        ivec2s center = (ivec2s){{winSize.x / 2, winSize.y / 2}};
        mousePos.x = mousePos.x - center.x;
        mousePos.y = (mousePos.y - center.y) * -1;
        float xRatio = self->camera.size.x / winSize.x;
        float yRatio = self->camera.size.y / winSize.y;
        self->mousePos.x = mousePos.x * xRatio;
        self->mousePos.y = mousePos.y * yRatio;
}

static ivec2s _getBoardPos(vec2s pos) {
        ivec2s boardPos = ivec2_zero();
        boardPos.x = (int)floor((pos.x / CELL_SIZE) + 4);
        boardPos.y = (int)floor((pos.y / CELL_SIZE) + 4);
        if (boardPos.x < 0 || boardPos.y < 0 ||
            boardPos.x > 7 || boardPos.y > 7) {
                boardPos.x = -1;
                boardPos.y = -1;
        }
        return boardPos;
}

static void _mouseClicked(struct Renderer *self) {
        if (state.window->mouseButtonsOnce[0]){
                state.window->mouseButtonsOnce[0] = false;
                ivec2s pos = _getBoardPos(self->mousePos);
        }
}

void renderUpdate(struct Renderer *self) {
        ivec2s windowSize = state.window->size;
        cameraResize(&self->camera, windowSize);
        _getMousePos(self, windowSize, state.window->mousePos);
        _mouseClicked(self);
        _createTransformations(self);
}

void renderEntities(struct Renderer *self, struct Positions *positions) {
        renderBoard(&self->board, _getBoardPos(self->mousePos));
        renderPieces(&self->piece, positions);
}

void renderDestroy(struct Renderer *self) {
        boardDelete(&self->board);
        pieceDelete(&self->piece);
}

