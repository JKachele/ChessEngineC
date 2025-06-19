/*************************************************
 *File----------board.c
 *Project-------ChessEngineC
 *Author--------Justin Kachele
 *Created-------Thursday Jun 19, 2025 13:33:33 EDT
 *License-------GNU GPL-3.0
 ************************************************/

#include "board.h"

static void _cellInit(struct Cell *self, int id) {
        self->id = id;

        // Rectangle
        float vertices[] = {
                // Position  // Texture
                1.0f, 1.0f,  0.25f, 0.25f,
                1.0f, 0.0f,  0.25f, 0.0f,
                0.0f, 0.0f,  0.0f, 0.0f,
                0.0f, 1.0f,  0.0f, 0.25f
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

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                        4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                        4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        float randX = (float)rand() / (float)(RAND_MAX/0.75);
        float randY = (float)rand() / (float)(RAND_MAX/0.75);
        self->texOffset = (vec2s){{randX, randY}};
}

void boardInit(struct Board *self) {
        for (int i = 0; i < 64; i++) {
                _cellInit(&self->cells[i], i);
        }
        loadTexture(&self->oakTexture, "oak.jpg", GL_RGB, false);
        loadTexture(&self->walnutTexture, "walnut.jpg", GL_RGB, false);
        shaderInit(&self->shader, "board");
}

void boardLoadTransforms(struct Board *self, mat4s view, mat4s projection) {
        shaderUse(&self->shader);
        GLuint viewLoc = glGetUniformLocation(self->shader.handle, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat*)&view.raw);

        GLuint projLoc = glGetUniformLocation(self->shader.handle, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const GLfloat*)&projection.raw);
}

static void _renderCell(struct Cell *self, struct Board *board,
                GLuint shaderHandle) {
        glBindVertexArray(self->vao);

        int xOffset = self->id % 8;
        int yOffset = self->id / 8;
        vec3s translate = {{xOffset * 8, yOffset * 8, 0.0f}};

        mat4s model = mat4_identity();
        model = glms_translate(model, translate);
        model = glms_scale(model, (vec3s){{8.0f, 8.0f, 1.0f}});

        GLuint modelLoc = glGetUniformLocation(shaderHandle, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)&model.raw);

        GLuint offsetLoc = glGetUniformLocation(shaderHandle, "texOffset");
        glUniform2fv(offsetLoc, 1, (const GLfloat*)self->texOffset.raw);

        glActiveTexture(GL_TEXTURE0);
        if ((xOffset + yOffset) % 2 == 0) {
                glBindTexture(GL_TEXTURE_2D, board->walnutTexture.handle);
        } else {
                glBindTexture(GL_TEXTURE_2D, board->oakTexture.handle);
        }

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void renderBoard(struct Board *self) {
        shaderUse(&self->shader);
        for (int i = 0; i < 64; i++) {
                _renderCell(&self->cells[i], self, self->shader.handle);
        }
}

void boardDelete(struct Board *self) {
        for (int i = 0; i < 64; i++) {
                glDeleteVertexArrays(1, &self->cells[i].vao);
                glDeleteBuffers(1, &self->cells[i].vbo);
                glDeleteBuffers(1, &self->cells[i].ebo);
        }
}

