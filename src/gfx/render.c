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

        for (int i = 0; i < 64; i++) {
                cellInit(&self->cells[i], i);
        }

        shaderInit(&self->cellShader, "cell");
        cameraInit(&self->camera);
}

void createTransformations(struct Renderer *self) {
        struct Camera *cam = &self->camera;
        mat4s view = mat4_identity();
        view = cam->getView(cam);

        GLuint viewLoc = glGetUniformLocation(self->cellShader.handle, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat*)&view.raw);

        mat4s projection = mat4_identity();
        projection = glms_ortho(cam->width.x, cam->width.y,
                                cam->height.x, cam->height.y, 0.1f, 100.0f);
        GLuint projLoc = glGetUniformLocation(self->cellShader.handle, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const GLfloat*)&projection.raw);
}

void renderUpdate(struct Renderer *self) {
        shaderUse(&self->cellShader);

        createTransformations(self);

        for (int i = 0; i < 64; i++) {
                renderCell(&self->cells[i], self->cellShader.handle);
        }
}

void renderDestroy(struct Renderer *self) {
        shaderDestroy(&self->cellShader);

        for (int i = 0; i < 64; i++) {
                cellDelete(&self->cells[i]);
        }
}

