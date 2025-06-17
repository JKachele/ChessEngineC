/*************************************************
 *File----------camera.c
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Monday Jun 16, 2025 17:25:34 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "camera.h"
#include "cglm/struct/vec3.h"

static mat4s getViewMatrix(struct Camera *self) {
        vec3s target = vec3_add(self->pos, self->front);
        return glms_lookat(self->pos, target, self->up);
}

void cameraInit(struct Camera *self) {
        self->pos = (vec3s){{0.0f, 0.0f, -3.0f}};
        self->front = (vec3s){{0.0f, 0.0f, -1.0f}};
        self->up = (vec3s){{0.0f, 1.0f, 0.0f}};

        self->fov = 45.0f;

        self->pitch = 0.0f;
        self->yaw = -90.0f;

        self->getView = getViewMatrix;
}

void moveCamera(struct Camera *self, float deltaTime, bool *keysPressed) {
        const float cameraSpeed = 2.5f * deltaTime;

        if (keysPressed[GLFW_KEY_W]) {
                vec3s newPos = vec3_add(self->pos,
                                vec3_scale(self->front, cameraSpeed));
                self->pos = newPos;
        }
        if (keysPressed[GLFW_KEY_S]) {
                vec3s newPos = vec3_sub(self->pos,
                                vec3_scale(self->front, cameraSpeed));
                self->pos = newPos;
        }
        if (keysPressed[GLFW_KEY_A]) {
                vec3s right = glms_normalize(glms_cross(self->front, self->up));
                vec3s newPos = vec3_sub(self->pos,
                                vec3_scale(right, cameraSpeed));
                self->pos = newPos;
        }
        if (keysPressed[GLFW_KEY_D]) {
                vec3s right = glms_normalize(glms_cross(self->front, self->up));
                vec3s newPos = vec3_add(self->pos,
                                vec3_scale(right, cameraSpeed));
                self->pos = newPos;
        }
        if (keysPressed[GLFW_KEY_SPACE]) {
                vec3s newPos = vec3_add(self->pos,
                                (vec3s){{0.0f, cameraSpeed, 0.0f}});
                self->pos = newPos;
        }
        if (keysPressed[GLFW_KEY_LEFT_SHIFT]) {
                vec3s newPos = vec3_sub(self->pos,
                                (vec3s){{0.0f, cameraSpeed, 0.0f}});
                self->pos = newPos;
        }
}

