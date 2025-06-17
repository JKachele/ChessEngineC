/*************************************************
 *File----------render.c
 *Project-------GameEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 12, 2025 13:06:45 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "render.h"


void renderInitOld(struct Renderer *self) {
        *self = (struct Renderer) {0};

        // Rectangle
        float vertices[] = {
                // Position           // color            // Texture
                 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
                 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
                -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f
        };

        unsigned int indices[] = {
                0, 1, 3,
                1, 2, 3
        };

        glGenBuffers(1, &self->vbo);
        glGenBuffers(1, &self->ebo);
        glGenVertexArrays(1, &self->vao);
        glBindVertexArray(self->vao);

        glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                        vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
                        indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                        8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                        8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        shaderInit(&self->shader);
        textureInit(&self->texture);

        glUniform1i(glGetUniformLocation(self->shader.handle, "Tex0"), 0);
        glUniform1i(glGetUniformLocation(self->shader.handle, "Tex1"), 1);
}

void renderInit(struct Renderer *self) {
        *self = (struct Renderer) {0};

        float vertices[] = {
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        glEnable(GL_DEPTH_TEST);

        glGenBuffers(1, &self->vbo);
        glGenVertexArrays(1, &self->vao);
        glBindVertexArray(self->vao);

        glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                        vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                        5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        shaderInit(&self->shader);
        textureInit(&self->texture);
        cameraInit(&self->camera);

        glUniform1i(glGetUniformLocation(self->shader.handle, "Tex0"), 0);
        // glUniform1i(glGetUniformLocation(self->shader.handle, "Tex1"), 1);
}

void createTransformations(struct Renderer *self) {
        struct Camera *cam = &self->camera;
        mat4s view = mat4_identity();
        view = cam->getView(cam);

        GLuint viewLoc = glGetUniformLocation(self->shader.handle, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat*)&view.raw);

        mat4s projection = mat4_identity();
        projection = glms_perspective(glm_rad(self->camera.fov),
                        800.0f / 600.0f, 0.1f, 100.0f);
        GLuint projLoc = glGetUniformLocation(self->shader.handle, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const GLfloat*)&projection.raw);
}

void renderBoxes(GLuint shaderHandle) {
        vec3s cubePositions[] = {
                (vec3s){{ 0.0f,  0.0f,   0.0f}},
                (vec3s){{ 2.0f,  5.0f, -15.0f}},
                (vec3s){{-1.5f, -2.2f,  -2.5f}},
                (vec3s){{-3.8f, -2.0f, -12.3f}},
                (vec3s){{ 2.4f, -0.4f,  -3.5f}},
                (vec3s){{-1.7f,  3.0f,  -7.5f}},
                (vec3s){{ 1.3f, -2.0f,  -2.5f}},
                (vec3s){{ 1.5f,  2.0f,  -2.5f}},
                (vec3s){{ 1.5f,  0.2f,  -1.5f}},
                (vec3s){{-1.3f,  1.0f,  -1.5f}},
        };

        for(unsigned int i = 0; i < 10; i++) {
                mat4s model = mat4_identity();
                model = glms_translate(model, cubePositions[i]);
                float angle = 20.0f * (i + 1);
                angle *= (float)glfwGetTime();
                model = glms_rotate(model, glm_rad(angle),
                                (vec3s){{1.0f, 0.3f, 0.5f}});
                GLuint modelLoc = glGetUniformLocation(shaderHandle, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)&model.raw);

                glDrawArrays(GL_TRIANGLES, 0, 36);
        }

}

void renderUpdate(struct Renderer *self) {
        shaderUse(&self->shader);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, self->texture.handle0);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, self->texture.handle1);

        createTransformations(self);

        glBindVertexArray(self->vao);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        renderBoxes(self->shader.handle);
}

void renderDestroy(struct Renderer *self) {
        shaderDestroy(&self->shader);

        glDeleteVertexArrays(1, &self->vao);
        glDeleteBuffers(1, &self->vbo);
        glDeleteBuffers(1, &self->ebo);
}

