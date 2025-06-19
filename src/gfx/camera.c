/*************************************************
 *File----------camera.c
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Monday Jun 16, 2025 17:25:34 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "camera.h"
#include "cglm/struct/vec3.h"

const float BOARD_SIZE = 64.0f;
const float MARGIN = 8.0f;

static mat4s getViewMatrix(struct Camera *self) {
        vec3s target = vec3_add(self->pos, self->front);
        return glms_lookat(self->pos, target, self->up);
}

void cameraInit(struct Camera *self) {
        self->pos = (vec3s){{0.0f, 0.0f, 3.0f}};
        self->front = (vec3s){{0.0f, 0.0f, -1.0f}};
        self->up = (vec3s){{0.0f, 1.0f, 0.0f}};

        self->width = (vec2s){{-16.0, 80.0}};
        self->height = (vec2s){{-16.0, 80.0}};

        self->getView = getViewMatrix;
}

void cameraResize(struct Camera *self, ivec2s size) {
        float ratio = (float)size.x / size.y;
        const float minSize = BOARD_SIZE + (2 * MARGIN);
        
        if (ratio > 1) {
                self->height = (vec2s){{MARGIN * -1, BOARD_SIZE + MARGIN}};
                float width = minSize * ratio;
                float margin = (width - BOARD_SIZE) / 2;
                self->width = (vec2s){{margin * -1, BOARD_SIZE + margin}};
        } else {
                self->width = (vec2s){{MARGIN * -1, BOARD_SIZE + MARGIN}};
                float height = minSize / ratio;
                float margin = (height - BOARD_SIZE) / 2;
                self->height = (vec2s){{margin * -1, BOARD_SIZE + margin}};
        }
}

