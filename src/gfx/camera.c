/*************************************************
 *File----------camera.c
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Monday Jun 16, 2025 17:25:34 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "camera.h"
#include "cglm/struct/ivec2.h"
#include "cglm/struct/vec3.h"

const float BOARD_SIZE = 64.0f;
const float MARGIN = 8.0f;

static mat4s getViewMatrix(struct Camera *self) {
        vec3s target = vec3_add(self->pos, self->front);
        return glms_lookat(self->pos, target, self->up);
}

static mat4s getProjection(struct Camera *self) {
        const float NearClip = 0.1f;
        const float FarClip = 100.0f;
        float halfWidth = self->size.x / 2;
        float halfHeight = self->size.y / 2;
        mat4s projection = glms_ortho(  halfWidth * -1,  halfWidth,
                                        halfHeight * -1, halfHeight,
                                        NearClip,        FarClip);
        return projection;
}

void cameraInit(struct Camera *self) {
        // self->pos = (vec3s){{0.0f, 0.0f, 3.0f}};
        self->pos = (vec3s){{32.0f, 32.0f, 3.0f}};
        self->front = (vec3s){{0.0f, 0.0f, -1.0f}};
        self->up = (vec3s){{0.0f, 1.0f, 0.0f}};

        self->size = (vec2s){{80.0f, 80.0f}};

        self->getView = getViewMatrix;
        self->getProjection = getProjection;
}

void cameraResize(struct Camera *self, ivec2s size) {
        static ivec2s windowSize = (ivec2s){{0, 0}};
        if (ivec2_eqv(windowSize, size))
                return;
        windowSize = size;


        float ratio = (float)size.x / size.y;
        const float minSize = BOARD_SIZE + (2 * MARGIN);
        
        if (ratio > 1) {
                float width = minSize * ratio;
                self->size.x = width;
                self->size.y = minSize;
        } else {
                float height = minSize / ratio;
                self->size.x = minSize;
                self->size.y = height;
        }
}

