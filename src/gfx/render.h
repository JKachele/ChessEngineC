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
#include "texture.h"
#include "camera.h"

struct Renderer {
        struct Shader shader;
        struct Texture texture;
        struct Camera camera;

        GLuint vao;
        GLuint vbo;
        GLuint ebo;
};

void renderInit(struct Renderer *self);
void renderUpdate(struct Renderer *self);
void renderDestroy(struct Renderer *self);

#endif

