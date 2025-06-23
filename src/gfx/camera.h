/*************************************************
 *File----------camera.h
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Monday Jun 16, 2025 17:25:31 EDT
 *License-------GNU GPL-3.0
 ************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#include "gfx.h"

struct Camera {
        vec3s pos;
        vec3s front;
        vec3s up;

        vec2s size;

        mat4s (*getView)(struct Camera *self);
        mat4s (*getProjection)(struct Camera *self);
};

void cameraInit(struct Camera *self);
void cameraResize(struct Camera *self, ivec2s size);

#endif

